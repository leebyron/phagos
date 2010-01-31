/*
 *  IntroGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "IntroGameState.h"
#include "ofMain.h"
#include "GameManager.h"

void IntroGameState::setup() {
  printf("intro game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  ofBackground(0, 1, 5);
}

void IntroGameState::update() {
  float elapsed = ofGetElapsedTimef() - timeStarted;
  if (elapsed > 1.5) {
    manager->setState(WAITING_FOR_PLAYERS);
  }
}

void IntroGameState::draw() {
  ofSetColor(0x000099);
	ofDrawBitmapString("intro state", 110, 130);
}

void IntroGameState::exit() {
  printf("intro game state teardown\n");
}
