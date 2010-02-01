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
  
  ofBackground(0,0,0);
}

void PlayingGameState::update() {
  PlayerManager* playerManager = PlayerManager::getManager();
  
  float elapsed = ofGetElapsedTimef() - timeStarted;
  
  if (elapsed > 300) { // TODO: what else actually triggers this?
    manager->setState(GAME_OVER);
  }
  
  // update creature creator
  Player* player;
  for (int i = 0; i < playerManager->numPlayers; i++) {
    player = playerManager->getPlayer(i);
    if (player->creatureCreator->targetLuminocity > 0 &&
        player->creatureCreator->remainingOoze > 0) {
      player->creatureCreator->remainingOoze =
        CLAMP(player->creatureCreator->remainingOoze - OOZE_USE_RATE, 0, 1);
    } else if (player->creatureCreator->remainingOoze < 1) {
      player->creatureCreator->remainingOoze =
        CLAMP(player->creatureCreator->remainingOoze + OOZE_RECOVERY_RATE, 0, 1);
    }
    playerManager->getPlayer(i)->creatureCreator->update();
  }

  CreatureWorld::getWorld()->updateWorld();
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
  Creature* creature;
  
  // draw all of the creatures on the screen please
  for (int i = 0; i < world->creatures.size(); i++) {
    world->creatures[i]->draw();
  }

  // draw all players' creators
  for (int i = 0; i < playerManager->numPlayers; i++) {
    playerManager->getPlayer(i)->creatureCreator->draw();
  }
}

void PlayingGameState::exit() {
  printf("play game state teardown\n");
}

void PlayingGameState::pressed(Player* player) {
  player->creatureCreator->targetLuminocity = 1.0;
}

void PlayingGameState::released(Player* player) {
  player->creatureCreator->targetLuminocity = 0.0;

  Creature* creature = CreatureWorld::getWorld()->spawnCreature(player,
                                                                ofRandom(1, 100),
                                                                ofRandom(1, 100),
                                                                ofRandom(1, 100));
}
