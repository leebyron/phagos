/*
 *  WaitingGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "WaitingGameState.h"
#include "ofMain.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "PhagosLogo.h"
#include "phagosConstants.h"
#include "Image.h"

void WaitingGameState::setup() {
  printf("waiting game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  
  // reset the controller situation
  PlayerManager::getManager()->clearPlayers();
  foundPlayers = 0;
  
  counterOrigin = (ofGetWidth() - 5 * 60) * 0.5 ;
  targetCounterOrigin = counterOrigin;

  ofBackground(0, 0, 0);
}

void WaitingGameState::update() {
  PlayerManager* playerManager = PlayerManager::getManager();
  
  if (foundPlayers != playerManager->numPlayers) {
    if (foundPlayers == 0) {
      playerTappedTime = ofGetElapsedTimef();
    }
    foundPlayers = playerManager->numPlayers;
    
    float countdownTime = WAITING_COUNTDOWN_TIME;
    if (foundPlayers == 1) {
      countdownTime = WAITING_COUNTDOWN_TIME_1;
    } else if (foundPlayers == MAX_PLAYERS) {
      countdownTime = WAITING_COUNTDOWN_TIME_MAX;
    }
    
    timeComplete = MAX(timeComplete, ofGetElapsedTimef() + countdownTime);
  }
  
  float remaining = timeComplete - ofGetElapsedTimef();

  if (foundPlayers > 0 && remaining <= 0) {
    manager->setState(PLAYING_GAME);
  }
  
  // update creature creators
  for (int i = 0; i < playerManager->numPlayers; i++) {
    playerManager->getPlayer(i)->creatureCreator->update();
  }

  // update logo
  PhagosLogo::getLogo()->update();

  if (foundPlayers > 0) {    
    float counterWidth = ceil(remaining) * 60;
    targetCounterOrigin = (ofGetWidth() - counterWidth) * 0.5;
    counterOrigin += 0.2 * (targetCounterOrigin - counterOrigin);
  }

}

void WaitingGameState::draw() {
  PlayerManager* playerManager = PlayerManager::getManager();
  GameManager* gameManager = GameManager::getManager();
  
  float fadeIn = sqAni(0.5 * (ofGetElapsedTimef() - timeStarted));
  
  // draw the background
  glPushMatrix();
  glScalef(1024, 1024, 1);
  glColor4f(fadeIn, fadeIn, fadeIn, 1);
  drawTexture(gameManager->backgroundImage);
  glPopMatrix();

  float remaining = timeComplete - ofGetElapsedTimef();

  // draw all players' creators
  for (int i = 0; i < playerManager->numPlayers; i++) {
    playerManager->getPlayer(i)->creatureCreator->draw();
  }
  
  // draw logo
  float logoAlpha = 1;
  if (playerManager->numPlayers > 0) {
    logoAlpha = 1 - sqAni((ofGetElapsedTimef() - playerTappedTime) * 3);
  }
  PhagosLogo::getLogo()->draw(logoAlpha);
  
  // draw counter
  if (playerManager->numPlayers > 0) {
    int counters = ceil(remaining);
    float counterWidth = (counters - 0.5) * 60;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glPushMatrix();
    glTranslatef(counterOrigin + counterWidth, 280, 0);
    for (int i = 0; i < counters; i++) {
      float counterAlpha = (1 - logoAlpha);
      
      if (i == 0) {
        counterAlpha *= sqAni((remaining - counters + 1) * 4);
      }
      glColor4f(1,1,1, 0.6 * counterAlpha);
      ofCircle(0, 0, 10);
      glTranslatef(-60, 0, 0);
    }
    glPopMatrix();
    glDisable(GL_BLEND);
  }
}

void WaitingGameState::exit() {
  printf("waiting game state teardown\n");
}

void WaitingGameState::pressed(Player* player) {
  player->creatureCreator->targetLuminocity = 1.0;
}

void WaitingGameState::released(Player* player) {
  player->creatureCreator->targetLuminocity = 0.0;
}
