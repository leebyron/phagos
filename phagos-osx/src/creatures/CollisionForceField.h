/*
 *  CollisionForceField.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/31/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "ofxMSAPhysics.h"
#include "phagosConstants.h"

class CreatureWorld;
class Creature;

class CollisionForceField : public ofxMSAPhysicsUpdater {
public:
  
  CollisionForceField();

  CreatureWorld* world;
  int n;
  Creature* _a;
  Creature* _b;
  float rA;
  float rB;
  float restLength;
  ofPoint delta;
  float deltaLength;
  float deltaLength2;
  float force;
  
  void update();
  
};
