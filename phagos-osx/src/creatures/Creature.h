/*
 *  Creature.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "ofxMSAPhysics.h"
#include "Player.h"

#define CREATURE_PARTICLE 0x123

class Food;

class Creature : public ofxMSAParticle {
public:

  Creature();
  ~Creature();
  
  // owner
  Player* player;

  // Stats! the good stuff
  float   size;
  float   hunger;
  float   speed;
  // how many have been constructed
  int stepsCompleted;
  
  // IN MAH BELLAY!
  list<Food*> foods;
  
  // true if the creature is in the wild now
  bool    released;
  float   timeReleased;
  
  bool    wasKilled;
  float   timeKilled;
  bool    wasLastOfKind;
  
  bool    isEating;

  // critter's motion
  float   angleV;
  float   angle;
  float   velocity;

  void update();
  void draw(float opacity);

  void unleash();
  void eatenBy(Creature* enemy);

};
