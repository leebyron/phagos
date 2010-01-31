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

static float hues[4] = {105, 43, 192, 299};

Player::Player(int playerNum, int joyNum) {
  this->playerNum     = playerNum;
  this->joyDeviceNum  = joyNum;
  joyButtonPressed    = 0;

  // make me a creature creator!
  creatureCreator = new CreatureCreator(this);

  // determine fancy things like color and placement
  // TODO: these colors should be pre-computed based on Ash's designs
  // and joysticks should always get the first colors, set the keyboard
  // users to always use the last 3 available colors
  color.setHSV(hues[joyNum], 1, 1);
  origin.x = playerNum == 0 ? 512 : 1200;
  origin.y = 650;
}

Player::~Player() {
  creatureCreator->release();
}
