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
  makeFixed();

  angle         = -HALF_PI;
  velocity      = 0;
}

Creature::~Creature() {
  // death to creature
}

void Creature::update() {
  CreatureWorld* world = CreatureWorld::getWorld();
  
  // called every frame by the physics engine
  setRadius(sqrt(size) * CREATURE_SIZE_SCALAR + CREATURE_SIZE_MIN);
  setMass(size * CREATURE_WEIGHT_SCALAR + CREATURE_WEIGHT_MIN);
  
  if (!released) {
    
    // do nothing yet
    return;
    
  } else {

    // movement?
    float angleDiff;
    
    // find closest critter on opposing team
    float closestDistance2 = 0;
    float d2 = 0;
    Creature* creature;
    Creature* closestCreature = NULL;
    ofPoint distanceToCreature;
    for (int i = 0; i < world->creatures.size(); i++) {
      creature = world->creatures[i];
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
    
    if (closestCreature == NULL) {
      angleDiff = ofRandomf() * 0.2;
    } else {
      distanceToCreature = *closestCreature - *this;
      float targetAngle = atan2(distanceToCreature.y, distanceToCreature.x);
      angleDiff = targetAngle - angle;
      WRAP_ANGLE(angleDiff);
    }
    
    float maxTurn = CREATURE_TURNING_MIN + (CREATURE_TURNING_SCALAR * speed);
    float maxVelocity = CREATURE_VELOCITY_MIN + (CREATURE_VELOCITY_SCALAR * speed);
    
    if (angleDiff > maxTurn) {
      angleDiff = maxTurn;
    } else if (angleDiff < -maxTurn) {
      angleDiff = -maxTurn;
    }

    // determine speed
    velocity = ofRandomuf() * maxVelocity;

    // add velocity from swimming
    angle += angleDiff;
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

  glPopMatrix();
}

void Creature::unleash() {
  released = true;
  makeFree();
}
