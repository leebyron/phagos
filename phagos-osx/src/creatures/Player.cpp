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

static float hues[8] = {43, 196, 297, 88, 26, 252, 158, 323};

Player::Player(int playerNum, int joyNum) {
  this->playerNum     = playerNum;
  this->joyDeviceNum  = joyNum;
  joyButtonPressed    = 0;

  // make me a creature creator!
  creatureCreator = new CreatureCreator(this);

  // determine fancy things like color and placement
  color.setHSV(hues[joyNum], 1, 1);
  origin.x = playerNum == 0 ? 512 : 1200;
  origin.y = 650;

  init();
}

// this is probably a rogue
Player::Player() {
  this->playerNum     = -1;
  this->joyDeviceNum  = -1;

  // no creature creator needed, plz!
  creatureCreator = NULL;

  // determine fancy things like color and placement
  color.set(0.6, 0.6, 0.6);
  //origin.x = playerNum == 0 ? 512 : 1200;
  //origin.y = 650;

  init();
}

Player::~Player() {
  printf("bye player.\n");
  if (creatureCreator) {
    creatureCreator->release();
  }
}

void Player::init() {
  creaturesInPlay = 0;
  hadBegun = false;
  stillPlaying = true;
}

void Player::gameOver() {

  stillPlaying = false;

  if (creatureCreator) {
    creatureCreator->creature = NULL;
    creatureCreator->targetOpacity = 0.3;
    creatureCreator->remainingOoze = 0;
  }

  // TODO: remove last creature in the creator ?
}
