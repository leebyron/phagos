/*
 *  phagosApp.cpp
 *  Phagos
 *
 *  This file is responsible for interfacing with events and delegating major
 *  actions to the game manager
 *
 *  Created by Lee Byron on 1/29/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "phagosApp.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "ofOSX.h"

//--------------------------------------------------------------
void phagosApp::setup() {
	counter = 0;
	ofSetCircleResolution(50);
	ofBackground(0,0,0);
	ofSetWindowTitle("Phagos");

  ofHideCursor();

  // data file
  ofSetDataPathRoot(getResourcesPath() + "/");

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void phagosApp::exit() {
	printf("BYE FOREVER\n");
}

//--------------------------------------------------------------
void phagosApp::update() {
  GameManager::getManager()->update();
}

//--------------------------------------------------------------
void phagosApp::draw() {
  GameManager::getManager()->draw();
}


//--------------------------------------------------------------
void phagosApp::keyPressed(int key) {
  // how many joysticks are there?
  int availableControllers = SDL_NumJoysticks();
  
  bool hitKey = false;
  int device = 0;
  if (key == SDLK_RSHIFT) {
    hitKey = true;
    device = availableControllers + 2;
  } else if (key == SDLK_LSHIFT) {
    hitKey = true;
    device = availableControllers + 1;
  } else if (key == SDLK_SPACE) {
    hitKey = true;
    device = availableControllers + 0;
  }
  
  // simulate a joystick
  if (hitKey) {
    joyButtonPressed(device, 1);
  }
}

//--------------------------------------------------------------
void phagosApp::keyReleased(int key) {
  // how many joysticks are there?
  int availableControllers = SDL_NumJoysticks();
  
  bool hitKey = false;
  int device = 0;
  if (key == SDLK_RSHIFT) {
    hitKey = true;
    device = availableControllers + 2;
  } else if (key == SDLK_LSHIFT) {
    hitKey = true;
    device = availableControllers + 1;
  } else if (key == SDLK_SPACE) {
    hitKey = true;
    device = availableControllers + 0;
  }
  
  // simulate a joystick
  if (hitKey) {
    joyButtonReleased(device, 1);
  }
}


//--------------------------------------------------------------
void phagosApp::joyButtonPressed(int device, int button) {
  if (device >= 8) {
    return; // where did you these high numbered devices!?!
  }
  
  GameManager* gameManager     = GameManager::getManager();
  PlayerManager* playerManager = PlayerManager::getManager();
  
  // if we're accepting new players, see if we can tap in.
  if (gameManager->isAcceptingNewPlayers()) {
    if (!(playerManager->hasPlayerForJoystick(device))) {
      Player* newPlayer = playerManager->addPlayer(device);
      printf("just added player %i on joy %i\n", newPlayer->playerNum, newPlayer->joyDeviceNum);
    }
  }

  if (!(playerManager->hasPlayerForJoystick(device))) {
    return;
  }

  Player* player = playerManager->getPlayerForJoystick(device);

  // only allow one button press at a time
  if (player->joyButtonPressed) {
    return;
  }
  player->joyButtonPressed = button;
  
  gameManager->pressed(player);
}

//--------------------------------------------------------------
void phagosApp::joyButtonReleased(int device, int button) {
  if (device >= 8) {
    return; // where did you these high numbered devices?!?
  }
  
  GameManager* gameManager     = GameManager::getManager();
  PlayerManager* playerManager = PlayerManager::getManager();
  
  if (!(playerManager->hasPlayerForJoystick(device))) {
    return;
  }

  Player* player = playerManager->getPlayerForJoystick(device);

  // only listen to the release of the button we're tracking
  if (player->joyButtonPressed != button) {
    return;
  }
  player->joyButtonPressed = 0;

  gameManager->released(player);
}

//--------------------------------------------------------------
void phagosApp::windowResized(int w, int h){

}
