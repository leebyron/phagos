/*
 *  Creature.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "ofxMSAPhysics.h"
#include "Player.h"

class Creature : public ofxMSAParticle {
public:

  Creature();
  ~Creature();
  
  Player* player;
  float   size;
  float   mouthSize;
  float   speed;
  bool    released;

};
