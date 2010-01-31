/*
 *  Player.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "Player.h"
#include "ofMain.h"

Player::Player(int playerNum, int joyNum) {
  this->playerNum     = playerNum;
  this->joyDeviceNum  = joyNum;
  joyButtonPressed    = 0;

  // determine fancy things like color and placement
  // TODO: these colors should be pre-computed based on Ash's designs
  // and joysticks should always get the first colors, set the keyboard
  // users to always use the last 3 available colors
  color.setHSV(joyNum * 130, 0.8, 0.8);
  origin.x = ofRandom(0, ofGetWidth());
  origin.y = ofRandom(0, ofGetHeight());
}

Player::~Player() {
}
