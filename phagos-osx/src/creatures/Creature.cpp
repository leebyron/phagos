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
  mouthSize     = 0;
  speed         = 0;

  released      = false;

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
    if (creature->player == player) {
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
    angleDiff = ofRandomuf();
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
  ofCircle(mouthX, mouthY, physicalSize * 0.4);

  // draw tail
  float tailX = -mouthX;
  float tailY = -mouthY;
  ofLine(tailX, tailY, tailX * physicalSize * 0.3, tailY * physicalSize * 0.3);

  glPopMatrix();
}
