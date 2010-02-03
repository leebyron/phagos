/*
 *  GameManager.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "GameManager.h"
#include "OpeningGameState.h"
#include "IntroGameState.h"
#include "WaitingGameState.h"
#include "PlayingGameState.h"
#include "OverGameState.h"
#include "phagosConstants.h"
#include "PlayerManager.h"
#include "Image.h"

static GameManager* instance = NULL;

GameManager* GameManager::getManager() {
  if (instance == NULL) {
    instance = new GameManager();
  }
  return instance;
}

GameManager::GameManager() {
  currentState = INITIAL_GAME_STATE;
  currentStateInstance = NULL;
  
  // load in the background
  backgroundImage = loadTexture("images/background.png", GL_BGR);
  
  // make a ring to use when things die
  ring = new ofxMSAShape3D();
  ring->begin(GL_TRIANGLE_STRIP);
  float x,y,a;
  float outerR = 1;
  float innerR = 0.8;
  float totalA = TWO_PI / (RING_RESOLUTION - 1);
  for (int i = 0; i < RING_RESOLUTION; i++) {
    a = totalA * i;
    x = cos(a - HALF_PI);
    y = sin(a - HALF_PI);
    ring->addVertex(x * outerR, y * outerR);
    ring->addVertex(x * innerR, y * innerR);
  }
  ring->end();
}

GameManager::~GameManager() {
}

void GameManager::update() {
  if (currentStateInstance) {
    currentStateInstance->update();
  } else {
    setState(currentState);
  }
}

void GameManager::draw() {
  if (currentStateInstance) {
    currentStateInstance->draw();
  }
}

void GameManager::pressed(Player* player) {
  if (currentStateInstance) {
    currentStateInstance->pressed(player);
  }
}

void GameManager::released(Player* player) {
  if (currentStateInstance) {
    currentStateInstance->released(player);
  }
}

void GameManager::setState(GameState newState) {
  if (currentStateInstance) {
    currentStateInstance->exit();
    currentStateInstance->release();
  }
  
  currentState = newState;
  
  switch (currentState) {
    case OPENING_SEQUENCE:
      currentStateInstance = new OpeningGameState();
      break;
    case INTRO_SEQUENCE:
      currentStateInstance = new IntroGameState();
      break;
    case WAITING_FOR_PLAYERS:
      currentStateInstance = new WaitingGameState();
      break;
    case PLAYING_GAME:
      currentStateInstance = new PlayingGameState();
      break;
    case GAME_OVER:
      currentStateInstance = new OverGameState();
      break;
    default:
      break;
  }
  
  currentStateInstance->manager = this;
  currentStateInstance->setup();
}

bool GameManager::isAcceptingNewPlayers() {
  return (currentState == WAITING_FOR_PLAYERS &&
          PlayerManager::getManager()->numPlayers < MAX_PLAYERS);
}
