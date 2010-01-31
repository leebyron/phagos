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

#define COUNTDOWN_TIME 3.0

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
    timeStarted = ofGetElapsedTimef();
  }
  float elapsed = ofGetElapsedTimef() - timeStarted;
    
  if (foundPlayers > 0 && elapsed > COUNTDOWN_TIME) {
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
    state += ofToString(COUNTDOWN_TIME - (ofGetElapsedTimef() - timeStarted), 2);
    state += "s";
  }
  
  ofSetColor(0x00AA00);
	ofDrawBitmapString(state, 120, 160);
}

void WaitingGameState::exit() {
  printf("waiting game state teardown\n");
}
