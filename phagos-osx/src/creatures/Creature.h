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
  int stepsCompleted;
  
  // true if the creature is in the wild now
  bool    released;
  bool    wasKilled;
  
  bool    isEating;

  // critter's motion
  float   angleV;
  float   angle;
  float   velocity;

  void update();
  void draw();
  
  void unleash();

};
