/*
 *  Player.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "ofxObjCPointer.h"
#include "ofxMSAUtils.h"
#include "CreatureCreator.h"

class Player : public ofxObjCPointer {
public:

  Player(int playerNum, int joyNum);
  ~Player();
  
  int playerNum;
  int joyDeviceNum;
  msaColor color;
  ofPoint origin;
  
  int creaturesInPlay;
  bool hadBegun;
  bool stillPlaying;
  
  // keep a pointer to your creature creator
  CreatureCreator* creatureCreator;
  
  // maintain button state
  int joyButtonPressed;
  
  void gameOver();

};
