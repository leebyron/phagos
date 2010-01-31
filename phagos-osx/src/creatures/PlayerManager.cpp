/*
 *  PlayerManager.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "PlayerManager.h"

static PlayerManager* instance;

PlayerManager* PlayerManager::getManager() {
  if (instance == NULL) {
    instance = new PlayerManager();
  }
  return instance;
}

PlayerManager::PlayerManager() {
  for (int i = 0; i < 8; i++) {
    players[i]      = NULL;
    playersByJoy[i] = NULL;
  }
  numPlayers = 0;
}

PlayerManager::~PlayerManager() {
}

void PlayerManager::clearPlayers() {
  for (int i = 0; i < numPlayers; i++) {
    playersByJoy[players[i]->joyDeviceNum] = NULL;
    players[i]->release();
    players[i] = NULL;
  }
  numPlayers = 0;
}

Player* PlayerManager::addPlayer(int joyNum) {
  if (numPlayers == 8) {
    printf("wtf, how did you get more than 8 controllers going.");
    return NULL;
  }

  Player* player        = new Player(numPlayers, joyNum);
  players[numPlayers]   = player;
  playersByJoy[joyNum]  = player;
  numPlayers++;
  
  return player;
}

Player* PlayerManager::getPlayer(int playerNum) {
  if (playerNum > numPlayers) {
    printf("cant get player %i when there are only %i players", playerNum, numPlayers);
    return NULL;
  }
  return players[playerNum];
}

bool PlayerManager::hasPlayerForJoystick(int joyNum) {
  return playersByJoy[joyNum] != NULL;
}

Player* PlayerManager::getPlayerForJoystick(int joyNum) {
  Player* player = playersByJoy[joyNum];
  if (player == NULL) {
    printf("no player for joystick %i", joyNum);
  }
  return player;
}
