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

Creature::Creature() {
  verbose       = false;

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
}

void Creature::update() {
  
  if (isDead()) {
    return;
  }
  
  // if we're dead, destroy!
  if (wasKilled || size <= 0) {
    released = false;
    kill();
    return;
  }

  CreatureWorld* world = CreatureWorld::getWorld();
  
  // called every frame by the physics engine
  setRadius(MAX(0, sqrt(size) * CREATURE_SIZE_SCALAR + CREATURE_SIZE_MIN));
  setMass(MAX(0, size * CREATURE_WEIGHT_SCALAR + CREATURE_WEIGHT_MIN));
  
  if (!released) {
    
    // do nothing yet
    // TODO: lifelike wiggles
    return;
    
  } else {
    
    // angle and speed is limited by creature ability
    float maxTurn = CREATURE_TURNING_MIN + (CREATURE_TURNING_SCALAR * speed);
    float maxVelocity = CREATURE_VELOCITY_MIN + (CREATURE_VELOCITY_SCALAR * speed);    
    
    // find closest critter on opposing team
    float closestDistance2 = 0;
    float d2 = 0;
    Creature* creature;
    Creature* closestCreature = NULL;
    ofPoint distanceToCreature;

    list<Creature*>::iterator it;
    for (it = world->creatures.begin(); it != world->creatures.end(); ++it) {
      creature = *it;
      if (creature->player == player || !(creature->released)) {
        continue;
      }

      distanceToCreature = *creature - *this;
      d2 = msaLengthSquared(distanceToCreature);
      if (closestCreature == NULL || d2 < closestDistance2) {
        closestCreature = creature;
        closestDistance2 = d2;
      }
    }
    
    // chase the closest creature!
    if (closestCreature == NULL) {
      angleV += 0.3 * ofRandomf() * maxTurn;
    } else {
      distanceToCreature = *closestCreature - *this;
      float targetAngle = atan2(distanceToCreature.y, distanceToCreature.x);
      angleV = targetAngle - angle;
      WRAP_ANGLE(angleV);
    }

    // if the closest creature is at our mouth, nom some points
    isEating = false;
    if (closestCreature) {
      float minDist = getRadius() + closestCreature->getRadius();
      //printf("eat if %f - %f < 100\n", sqrtf(closestDistance2), minDist, 100);
      if (sqrtf(closestDistance2) - minDist < NOM_DISTANCE) {
        // part of being able to eat is having your mouth in the right place
        // the most epic eater can nom with 30deg CREATURE_EATING_ANGLE in either direction
        // but minimum of 5 deg in either angle CREATURE_EATING_ANGLE_MIN on a easing basis
        float maxAngle = hunger * CREATURE_EATING_ANGLE + CREATURE_EATING_ANGLE_MIN;
        float eatAngleLinear = (maxAngle - ABS(angleV)) / maxAngle;

        if (eatAngleLinear > 0) {
          float eatingSpeed = hunger * CREATURE_EATING_SPEED + CREATURE_EATING_MIN;
          float eatAngle = sqrtf(eatAngleLinear);
          eatingSpeed *= eatAngle;

          if (eatingSpeed > closestCreature->size) {
            closestCreature->wasKilled = true;
            eatingSpeed = closestCreature->size;
          }
          closestCreature->size -= eatingSpeed;
          size += eatingSpeed * POINTS_EATEN_EFFICIENCY;
          isEating = true;
        }
      }
    }
    
    // use some metabolism!
    size -= PER_FRAME_METABOLISM;

    if (angleV > maxTurn) {
      angleV = maxTurn;
    } else if (angleV < -maxTurn) {
      angleV = -maxTurn;
    }

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
void Creature::draw() {
  
  float physicalSize = getRadius();
  
  if (player) {
    glColor4f(player->color.r,
              player->color.g,
              player->color.b,
              player->color.a);
  } else {
    // rogue!
    glColor4f(0.1, 0.1, 0.1, 0.5);
  }

  // move to critter center
  glPushMatrix();
  glTranslatef(x, y, 0);

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
  float tailLength = speed * CREATURE_TAIL_LENGTH; // * physicalSize;
  ofLine(tailX, tailY, tailX * tailLength, tailY * tailLength);
  
  if (isEating) {
    glColor4f(1,0,0,1);
    ofCircle(0, 0, physicalSize * 0.5);
  }

  glPopMatrix();
}

void Creature::unleash() {
  released = true;
  makeFree();
}
