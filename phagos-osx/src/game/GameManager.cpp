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
#include "PreparingGameState.h"
#include "PlayingGameState.h"
#include "OverGameState.h"

static GameManager* gameManager;

GameManager::GameManager() {
  currentState = INITIAL_STATE;
  currentStateInstance = NULL;

  gameManager = this;
}

GameManager::~GameManager() {
}

GameManager* GameManager::getManager() {
  return gameManager;
}

void GameManager::update() {
  if (currentStateInstance) {
    currentStateInstance->update();
  } else {
    setState(OPENING_SEQUENCE);
  }
}

void GameManager::draw() {
  if (currentStateInstance) {
    currentStateInstance->draw();
  }
}

void GameManager::setState(GameState newState) {
  if (currentStateInstance) {
    currentStateInstance->exit();
    currentStateInstance->release();
  }
  
  currentState = newState;
  
  switch (currentState) {
    case INITIAL_STATE:
      currentStateInstance = NULL;
      break;
    case OPENING_SEQUENCE:
      currentStateInstance = new OpeningGameState();
      break;
    case INTRO_SEQUENCE:
      currentStateInstance = new IntroGameState();
      break;
    case WAITING_FOR_PLAYERS:
      currentStateInstance = new WaitingGameState();
      break;
    case PREPARING_GAME:
      currentStateInstance = new PreparingGameState();
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
  return (currentState == WAITING_FOR_PLAYERS);
}
