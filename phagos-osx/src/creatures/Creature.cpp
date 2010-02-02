/*
 *  Creature.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "Creature.h"
#include "phagosConstants.h"
#include "CreatureWorld.h"
#include "Food.h"

Creature::Creature() {
  verbose       = false;
  type          = CREATURE_PARTICLE;

  size          = 0;
  hunger        = 0;
  speed         = 0;
  stepsCompleted = 0;

  // start as a static element
  released      = false;
  wasKilled     = false;
  isEating      = false;
  makeFixed();

  angle         = -HALF_PI;
  angleV        = 0;
  velocity      = 0;
}

Creature::~Creature() {
  // death to creature
  //printf("bye creature!\n");

  // remove all foods
  list<Food*>::iterator foodIter = foods.begin(); 
  Food* food;
  while (foodIter != foods.end()) {
    food = *foodIter;
    food->release();
    foodIter++;
  }
  foods.clear();
}



void Creature::unleash() {
  released = true;
  makeFree();
  player->creaturesInPlay++;
  player->hadBegun = true;
}

// called every frame by the physics engine
void Creature::update() {
  
  if (isDead()) {
    return;
  }
  
  // if we're dead, destroy!
  if (wasKilled || size <= 0) {
    // release all foods back into play
    list<Food*>::iterator foodIter;
    Food* food;
    for (foodIter = foods.begin(); foodIter != foods.end(); ++foodIter) {
      food = *foodIter;
      food->releasedFrom(this);
      food->release();
    }
    foods.clear();

    // kill the creature
    player->creaturesInPlay--;
    if (player->creaturesInPlay == 0) {
      player->gameOver();
    }
    released = false;
    kill();
    return;
  }

  CreatureWorld* world = CreatureWorld::getWorld();

  // called every frame by the physics engine
  float creatureMass = MAX(0, size * CREATURE_SIZE_SCALAR + CREATURE_SIZE_MIN);
  creatureMass += foods.size() * FOOD_SIZE * FOOD_SPACING_IN_BELLY;
  setRadius(sqrt(creatureMass));
  setMass(MAX(0, size * CREATURE_WEIGHT_SCALAR + CREATURE_WEIGHT_MIN));

  if (!released) {
    
    // do nothing yet
    // TODO: more lifelike wiggles
    float maxTurn = CREATURE_TURNING_MIN + (CREATURE_TURNING_SCALAR * speed);
    angleV += ofRandomf() * (0.1 + maxTurn * 0.2);

    if (angleV > maxTurn) {
      angleV = maxTurn;
    } else if (angleV < -maxTurn) {
      angleV = -maxTurn;
    }
    
    // angle drag
    angleV *= 0.97;
    
    // angle
    angle += angleV;
    
    // angle reset to 0 force
    angle += HALF_PI;
    angle *= 0.97;
    angle -= HALF_PI;
    
    
    return;
    
  } else {
    
    // angle and speed is limited by creature ability
    float maxTurn = CREATURE_TURNING_MIN + (CREATURE_TURNING_SCALAR * speed);
    float maxVelocity = CREATURE_VELOCITY_MIN + (CREATURE_VELOCITY_SCALAR * speed);    
    
    // find closest thing!
    float closestDistance2 = 0;
    float rawClosestDistance2 = 0;
    float d2 = 0;
    float desireDistance = 0;
    
    ofxMSAParticle* closestThing = NULL;
    ofPoint distanceToThing;
    bool thingIsCreature = true;

    // closest critter on opposing team
    Creature* creature;
    list<Creature*>::iterator it;
    for (it = world->creatures.begin(); it != world->creatures.end(); ++it) {
      creature = *it;
      if (creature->player == player || !(creature->released)) {
        continue;
      }

      distanceToThing = *creature - *this;
      d2 = msaLengthSquared(distanceToThing);
      desireDistance = d2 * CREATURE_DESIRE;
      if (closestThing == NULL || desireDistance < closestDistance2) {
        closestThing = creature;
        closestDistance2 = desireDistance;
        rawClosestDistance2 = d2;
      }
    }

    // closest food perhaps?
    Food* food;
    list<Food*>::iterator footIter;
    for (footIter = world->foods.begin(); footIter != world->foods.end(); ++footIter) {
      food = *footIter;
      if (!(food->isEdible())) continue;
      
      distanceToThing = *food - *this;
      d2 = msaLengthSquared(distanceToThing);
      desireDistance = d2 * FOOD_DESIRE - FOOD_DESIRE_OFFSET;
      if (closestThing == NULL || desireDistance < closestDistance2) {
        closestThing = food;
        closestDistance2 = desireDistance;
        rawClosestDistance2 = d2;
        thingIsCreature = false;
      }
    }
    
    // chase the closest thing!
    if (closestThing == NULL) {
      angleV += 0.3 * ofRandomf() * maxTurn;
    } else {
      distanceToThing = *closestThing - *this;
      float targetAngle = atan2(distanceToThing.y, distanceToThing.x);
      angleV = targetAngle - angle;
      WRAP_ANGLE(angleV);
    }

    // if the closest creature is at our mouth, nom some points
    isEating = false;
    if (closestThing) {
      float minDist = getRadius() + closestThing->getRadius();
      //printf("eat if %f - %f < 100\n", sqrtf(closestDistance2), minDist, 100);
      if (sqrtf(rawClosestDistance2) - minDist < NOM_DISTANCE) {
        // part of being able to eat is having your mouth in the right place
        // the most epic eater can nom with 30deg CREATURE_EATING_ANGLE in either direction
        // but minimum of 5 deg in either angle CREATURE_EATING_ANGLE_MIN on a easing basis
        float maxAngle = hunger * CREATURE_EATING_ANGLE + CREATURE_EATING_ANGLE_MIN;
        float eatAngleLinear = (maxAngle - ABS(angleV)) / maxAngle;

        if (eatAngleLinear > 0) {
          float eatingSpeed = hunger * CREATURE_EATING_SPEED + CREATURE_EATING_MIN;
          float eatAngle = sqrtf(eatAngleLinear);
          eatingSpeed *= eatAngle;
          
          isEating = true;
          
          if (thingIsCreature) {

            // chew a creature
            Creature* creatureChoobl = (Creature*)closestThing;
            if (eatingSpeed > creatureChoobl->size) {
              creatureChoobl->wasKilled = true;
              eatingSpeed = creatureChoobl->size;
            }
            creatureChoobl->size -= eatingSpeed;
            size += eatingSpeed * POINTS_EATEN_EFFICIENCY;
            
          } else {
            
            // eat a food
            Food* foodChoobl = (Food*)closestThing;
            if (eatAngle > 0.5) {
              foodChoobl->eatenBy(this);
              foods.push_back(foodChoobl);
              foodChoobl->retain();
            }
            
          }
        }
      }
    }
    
    // use some metabolism!
    size -= PER_FRAME_METABOLISM;
    
    
    // set the radius and mass according to the creatures size!
    float creatureMass = MAX(0, size * CREATURE_SIZE_SCALAR + CREATURE_SIZE_MIN);
    creatureMass += foods.size() * SQ(FOOD_SIZE * FOOD_SPACING_IN_BELLY);
    setRadius(sqrt(creatureMass));
    setMass(creatureMass);


    // limit angle based on agility/speed
    if (angleV > maxTurn) {
      angleV = maxTurn;
    } else if (angleV < -maxTurn) {
      angleV = -maxTurn;
    }
    
    // angle drag
    angleV *= 0.97;

    // determine speed
    velocity = ofRandomuf() * maxVelocity;

    // add velocity from swimming
    angle += angleV;
    ofPoint swimVelo;
    swimVelo.x = cos(angle) * velocity;
    swimVelo.y = sin(angle) * velocity;  
    addVelocity(swimVelo);
  }
}

// called manually by our code to draw
void Creature::draw(float opacity = 1.0) {
  float physicalSize = getRadius();

  // move to critter center
  glPushMatrix();
  glTranslatef(x, y, 0);
  
  // draw critter
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (player) {
    glColor4f(player->color.r,
              player->color.g,
              player->color.b,
              opacity);
  } else {
    // rogue!
    glColor4f(0.7, 0.7, 0.7, opacity);
  }
  
  // draw body
  ofCircle(0, 0, physicalSize);

  // draw mouth
  float mouthX = cos(angle) * physicalSize;
  float mouthY = sin(angle) * physicalSize;
  float mouthSize = hunger * CREATURE_MOUTH_SIZE; // * physicalSize;
  ofCircle(mouthX, mouthY, mouthSize);

  // draw tail
  float tailX = -mouthX;
  float tailY = -mouthY;
  float tailLength = 1 + (speed * CREATURE_TAIL_LENGTH); // * physicalSize;
  ofLine(tailX, tailY, tailX * tailLength, tailY * tailLength);
  
  if (isEating) {
    glColor4f(1,0,0,1);
    ofCircle(0, 0, physicalSize * 0.5);
  }

  glDisable(GL_BLEND); // end drawing critter

  // draw foods
  glPushMatrix();
  glRotatef(RAD_TO_DEG * angle, 0, 0, 1);

  list<Food*>::iterator foodIter;
  Food* food;
  float a = 0;
  float r = 0;
  for (foodIter = foods.begin(); foodIter != foods.end(); ++foodIter) {
    food = *foodIter;
    // TODO: draw foods not overlapping? or wobbling about? or something...

    glPushMatrix();
    glRotatef(360 * a, 0, 0, 1);
    glTranslatef(sqrt(r), 0, 0);
    food->drawFoodAtOrigin(opacity);
    glPopMatrix();

    r += SQ(FOOD_SIZE * 1.2);
    a += 1.618;
  }
  glPopMatrix(); // end drawing food

  glPopMatrix();
}
