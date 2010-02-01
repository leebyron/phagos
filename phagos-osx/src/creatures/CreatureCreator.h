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
class Creature;

class CreatureCreator : public ofxObjCPointer {
public:
  
  CreatureCreator(Player* player);
  ~CreatureCreator();
  
  // game stats
  Player* player;
  float remainingOoze;
  Creature* creature;
  
  // assembly stats
  float timePressed;
  int numFramesSincePress;
  bool isPressed;

  // drawing stats
  float luminocity;
  float radius;
  float opacity;
  float targetLuminocity;
  float targetRadius;
  float targetOpacity;
  float targetX;

  void update();
  void draw();
  
  void pressed();
  void released();

};
