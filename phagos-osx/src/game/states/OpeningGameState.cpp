/*
 *  OpeningGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "OpeningGameState.h"
#include "ofMain.h"
#include "GameManager.h"

void OpeningGameState::setup() {
  printf("opening game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  ofBackground(0, 0, 0);
}

void OpeningGameState::update() {  
  float elapsed = ofGetElapsedTimef() - timeStarted;
  if (elapsed > 1.5) {
    manager->setState(INTRO_SEQUENCE);
  }
}

void OpeningGameState::draw() {
  ofSetColor(0x222222);
	ofDrawBitmapString("opening state", 100, 100);
}

void OpeningGameState::exit() {
  printf("opening game state teardown\n");
}
