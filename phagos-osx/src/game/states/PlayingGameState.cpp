/*
 *  PlayingGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "PlayingGameState.h"
#include "ofMain.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "CreatureWorld.h"
#include "Creature.h"
#include "Image.h"
#include "phagosConstants.h"

void PlayingGameState::setup() {
  printf("play game state setup\n");

  CreatureWorld::getWorld()->resetWorld();

  timeStarted = ofGetElapsedTimef();
  gameWasWon = false;
  timeGameWasWon = 0;

  ofBackground(0, 0, 0);
}

void PlayingGameState::update() {
  PlayerManager* playerManager = PlayerManager::getManager();
  
  float elapsed = ofGetElapsedTimef() - timeStarted;
  
  if (//elapsed > 300 || // TODO: should 5 minutes actually end the game?
      (gameWasWon && ofGetElapsedTimef() - timeGameWasWon > 12.0)) {
    manager->setState(GAME_OVER);
  }
  
  // update creature creator
  Player* player;
  for (int i = 0; i < playerManager->numPlayers; i++) {
    player = playerManager->getPlayer(i);
    player->creatureCreator->update();
  }

  CreatureWorld::getWorld()->updateWorld();

  // is there a winning condition?
  int playersAlive = 0;
  for (int i = 0; i < playerManager->numPlayers; i++) {
    player = playerManager->getPlayer(i);
    if (player->stillPlaying) {
      playersAlive++;
    }
  }

  if (playersAlive == 1 && !gameWasWon) {
    printf("Multiplayer win condition met.");
    gameWasWon = true;
    timeGameWasWon = ofGetElapsedTimef();
  }
}

void PlayingGameState::draw() {
  GameManager* gameManager = GameManager::getManager();
  PlayerManager* playerManager = PlayerManager::getManager();
  
  // draw the background
  glPushMatrix();
  glScalef(1024, 1024, 1);
  glColor4f(1,1,1, 1);
  drawTexture(gameManager->backgroundImage);
  glPopMatrix();
  
  CreatureWorld* world = CreatureWorld::getWorld();
  
  // draw all of the creatures on the screen please
  list<Creature*>::iterator it;
  Creature* creature;
  for (it=world->creatures.begin(); it!=world->creatures.end(); ++it) {
    creature = *it;
    creature->draw(1.0);
  }
  
  // draw all players' creators
  for (int i = 0; i < playerManager->numPlayers; i++) {
    playerManager->getPlayer(i)->creatureCreator->draw();
  }
  
  // someone win? fade to black
  if (gameWasWon) {
    float fadeToBlack = sqAni((ofGetElapsedTimef() - (timeGameWasWon + 9.0)) / 3.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, fadeToBlack);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    glDisable(GL_BLEND);
  }
}

void PlayingGameState::exit() {
  printf("play game state teardown\n");
}

void PlayingGameState::pressed(Player* player) {
  player->creatureCreator->targetLuminocity = 1.0;
  player->creatureCreator->pressed();
}

void PlayingGameState::released(Player* player) {
  player->creatureCreator->targetLuminocity = 0.0;
  player->creatureCreator->released();
}
