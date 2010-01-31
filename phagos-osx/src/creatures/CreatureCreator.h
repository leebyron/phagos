/*
 *  CreatureCreator.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "ofxObjCPointer.h"

class Player;

class CreatureCreator : public ofxObjCPointer {
public:
  
  CreatureCreator(Player* player);
  ~CreatureCreator();
  
  Player* player;
  float remainingOoze;

  float luminocity;
  float radius;
  float opacity;
  float targetLuminocity;
  float targetRadius;
  float targetOpacity;
  float targetX;

  void update();
  void draw();

};
