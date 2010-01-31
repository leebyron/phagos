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
#include "PhagosLogo.h"

void IntroGameState::setup() {
  printf("intro game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  ofBackground(0, 0, 0);
}

void IntroGameState::update() {
  float elapsed = ofGetElapsedTimef() - timeStarted;
  if (elapsed > 6.0) {
    manager->setState(WAITING_FOR_PLAYERS);
  }
  
  PhagosLogo::getLogo()->update();
}

void IntroGameState::draw() {
  PhagosLogo::getLogo()->draw(1);
}

void IntroGameState::exit() {
  printf("intro game state teardown\n");
}
