/*
 *  Player.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "Player.h"

Player::Player(int playerNum, int joyNum) {
  this->playerNum = playerNum;
  this->joyDeviceNum = joyNum;

  // determine fancy things like color and placement
  creatureColor.setHSV(playerNum * 130, 0.8, 0.8);
  origin.x = 0;
  origin.y = 0;
}

Player::~Player() {
  
}
