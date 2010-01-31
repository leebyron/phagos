/*
 *  WaitingGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "WaitingGameState.h"
#include "ofMain.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "phagosConstants.h"

void WaitingGameState::setup() {
  printf("waiting game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  // reset the controller situation
  PlayerManager::getManager()->clearPlayers();
  foundPlayers = 0;
  
  ofSetColor(30, 30, 30);
}

void WaitingGameState::update() {
  if (foundPlayers != PlayerManager::getManager()->numPlayers) {
    foundPlayers = PlayerManager::getManager()->numPlayers;
    
    float countdownTime = WAITING_COUNTDOWN_TIME;
    if (foundPlayers == 1) {
      countdownTime = WAITING_COUNTDOWN_TIME_1;
    } else if (foundPlayers == MAX_PLAYERS) {
      countdownTime = WAITING_COUNTDOWN_TIME_MAX;
    }
    
    timeStarted = MAX(timeStarted, ofGetElapsedTimef() + countdownTime);
  }
  
  float remaining = timeStarted - ofGetElapsedTimef();

  if (foundPlayers > 0 && remaining <= 0) {
    manager->setState(PREPARING_GAME);
  }
}

void WaitingGameState::draw() {
  string state = "waiting state";
  
  if (PlayerManager::getManager()->numPlayers) {
    state += ": ";
    state += ofToString(PlayerManager::getManager()->numPlayers);
    state += " players";
  }
  
  if (foundPlayers) {
    state += " - ";
    state += ofToString(timeStarted - ofGetElapsedTimef(), 2);
    state += "s";
  }
  
  ofSetColor(0x00AA00);
	ofDrawBitmapString(state, 120, 160);
}

void WaitingGameState::exit() {
  printf("waiting game state teardown\n");
}

void WaitingGameState::pressed(Player* player) {
  printf("pressed by %i\n", player->playerNum);
}

void WaitingGameState::released(Player* player) {
  printf("released by %i\n", player->playerNum);
}
