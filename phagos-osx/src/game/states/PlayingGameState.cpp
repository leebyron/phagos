/*
 *  PlayingGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "PlayingGameState.h"
#include "ofMain.h"
#include "GameManager.h"

void PlayingGameState::setup() {
  printf("play game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  ofBackground(0,0,0);
}

void PlayingGameState::update() {
  
  float elapsed = ofGetElapsedTimef() - timeStarted;
  
  if (elapsed > 5) { //TODO: what actually triggers this?
    manager->setState(GAME_OVER);
  }
}

void PlayingGameState::draw() {
  ofSetColor(0x6600FF);
  
  string state = "playing state";
	ofDrawBitmapString(state, 140, 220);
}

void PlayingGameState::exit() {
  printf("play game state teardown\n");
}
