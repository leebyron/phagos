/*
 *  OverGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "OverGameState.h"
#include "ofMain.h"
#include "GameManager.h"

void OverGameState::setup() {
  printf("over game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  ofBackground(0,0,0);
}

void OverGameState::update() {
  float elapsed = ofGetElapsedTimef() - timeStarted;
  
  if (elapsed > 3.0) {
    manager->setState(INTRO_SEQUENCE);
  }
}

void OverGameState::draw() {
  // do nothing, glorious nothing.
}

void OverGameState::exit() {
  printf("over game state teardown\n");
}
