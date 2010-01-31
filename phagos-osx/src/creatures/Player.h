/*
 *  Player.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "ofxObjCPointer.h"
#include "ofxMSAUtils.h"

class Player : public ofxObjCPointer {
public:

  Player(int playerNum, int joyNum);
  ~Player();
  
  int playerNum;
  int joyDeviceNum;
  msaColor color;
  ofPoint origin;
  
  // maintain button state
  int joyButtonPressed;

};
