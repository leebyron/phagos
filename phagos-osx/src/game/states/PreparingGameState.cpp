/*
 *  PreparingGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "PreparingGameState.h"
#include "ofMain.h"
#include "GameManager.h"

void PreparingGameState::setup() {
  printf("preparing game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  ofBackground(0,0,0);
}

void PreparingGameState::update() {
  float elapsed = ofGetElapsedTimef() - timeStarted;

  if (elapsed > 1.5) {
    manager->setState(PLAYING_GAME);
  }
}

void PreparingGameState::draw() {
  ofSetColor(0xFF3300);
  
  string state = "preparing state";
	ofDrawBitmapString(state, 130, 190);
}

void PreparingGameState::exit() {
  printf("preparing game state teardown\n");
}
