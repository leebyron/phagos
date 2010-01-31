/*
 *  phagosApp.cpp
 *  Phagos
 *
 *  This file is responsible for interfacing with events and delegating major
 *  actions to their respective classes
 *
 *  Created by Lee Byron on 1/29/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "phagosApp.h"
#include "Player.h"

//--------------------------------------------------------------
void phagosApp::setup() {
	counter = 0;
	ofSetCircleResolution(50);
	ofBackground(0,0,0);
	bSmooth = false;
	ofSetWindowTitle("graphics example");

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

  // create objects
  gameManager     = new GameManager();
  playerManager   = new PlayerManager();
  world           = new CreatureWorld();

  // set up the first time
  world->initWorld();
}

//--------------------------------------------------------------
void phagosApp::exit() {
	printf("BYE FOREVER\n");

  delete world;
  delete playerManager;
}

//--------------------------------------------------------------
void phagosApp::update() {
  world->updateWorld();
  gameManager->update();
}

//--------------------------------------------------------------
void phagosApp::draw() {
  // draw the game!
  gameManager->draw();
}


//--------------------------------------------------------------
void phagosApp::keyPressed(int key) {
	if (key == 's'){
		bSmooth = !bSmooth;
	}
}

//--------------------------------------------------------------
void phagosApp::keyReleased(int key) {
}


//--------------------------------------------------------------
void phagosApp::joyButtonPressed(int device, int button) {
  
  // if we're accepting new players, see if we can tap in.
  if (gameManager->isAcceptingNewPlayers()) {
    if (!(playerManager->hasPlayerForJoystick(device))) {
      Player* newPlayer = playerManager->addPlayer(device);
      printf("just added player %i on joy %i\n", newPlayer->playerNum, newPlayer->joyDeviceNum);
    }
  }
  
  if (playerManager->hasPlayerForJoystick(device)) {
    Player* player = playerManager->getPlayerForJoystick(device);
    printf("player %i pressed button %i\n", player->playerNum, button);
  }

}

//--------------------------------------------------------------
void phagosApp::joyButtonReleased(int device, int button) {
  if (!(playerManager->hasPlayerForJoystick(device))) {
    return;
  }
  
  Player* player = playerManager->getPlayerForJoystick(device);
  printf("player %i released button %i\n", player->playerNum, button);
}

//--------------------------------------------------------------
void phagosApp::windowResized(int w, int h){

}
