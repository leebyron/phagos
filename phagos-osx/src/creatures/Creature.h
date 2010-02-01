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
  float   mouthSize;
  float   speed;
  
  // true if the creature is in the wild now
  bool    released;

  // critter's motion
  float   angle;
  float   velocity;

  void update();
  void draw();

};
