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
#include "Food.h"
#include "Image.h"
#include "phagosConstants.h"

void PlayingGameState::setup() {
  printf("play game state setup\n");
  ofBackground(0, 0, 0);
  
  CreatureWorld::getWorld()->resetWorld();

  timeStarted = ofGetElapsedTimef();
  gameWasWon = false;
  timeGameWasWon = 0;

  roguePlayer = new Player();
}

void PlayingGameState::exit() {
  printf("play game state teardown\n");

  CreatureWorld::getWorld()->resetWorld();
  PlayerManager::getManager()->clearPlayers();
  roguePlayer->release();
}

void PlayingGameState::update() {  
  // switch at end of fade to black
  if (gameWasWon && ofGetElapsedTimef() - timeGameWasWon > 12.0) {
    manager->setState(GAME_OVER);
  }
  
  // update creature creators
  PlayerManager* playerManager = PlayerManager::getManager();
  Player* player;
  for (int i = 0; i < playerManager->numPlayers; i++) {
    player = playerManager->getPlayer(i);
    player->creatureCreator->update();
  }
  
  if (!gameWasWon) {
    checkForWinningCondition();
    
    // should we spawn random shit?
    spawnRandomElements();
  }

  // update world
  CreatureWorld::getWorld()->updateWorld();
}

// ------------------------------------------------------------------
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
  list<Creature*>::iterator creatureIter;
  Creature* creature;
  for (creatureIter = world->creatures.begin(); creatureIter != world->creatures.end(); ++creatureIter) {
    creature = *creatureIter;
    if (creature->isDead()) {
      printf("found a dead creature in my list?");
    }
    creature->draw(1.0);
  }

  // draw all of the foods on the screen please
  list<Food*>::iterator foodIter;
  Food* food;
  for (foodIter = world->foods.begin(); foodIter != world->foods.end(); ++foodIter) {
    food = *foodIter;
    food->draw();
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

void PlayingGameState::pressed(Player* player) {
  player->creatureCreator->targetLuminocity = 1.0;
  player->creatureCreator->pressed();
}

void PlayingGameState::released(Player* player) {
  player->creatureCreator->targetLuminocity = 0.0;
  player->creatureCreator->released();
}

// ==================================================================
// Overarching Game Logic 
// ==================================================================

// ------------------------------------------------------------------
void PlayingGameState::checkForWinningCondition() {
  float elapsed = ofGetElapsedTimef() - timeStarted;
  
  // TODO: 5 minutes ends the game in a tie.
  if (elapsed > 300) {
    printf("Out of time, tie.\n");
    gameWasWon = true;
    timeGameWasWon = ofGetElapsedTimef();
    return;
  }

  PlayerManager* playerManager = PlayerManager::getManager();
  Player* player;

  // check for multiplayer winning condition
  if (playerManager->numPlayers > 1) {

    int playersAlive = 0;
    Player* lastRemaining = NULL;
    for (int i = 0; i < playerManager->numPlayers; i++) {
      player = playerManager->getPlayer(i);
      if (player->stillPlaying) {
        playersAlive++;
        lastRemaining = player;
      }
    }

    if (playersAlive == 0) {
      printf("Destroyed by rogues.\n");
      gameWasWon = true;
      timeGameWasWon = ofGetElapsedTimef();
      return;
    } else if (playersAlive == 1) {
      // TODO: lastRemaining vs rogue, what are the conditions to win then? similar to single player?
      printf("Multiplayer win condition met.\n");
      gameWasWon = true;
      timeGameWasWon = ofGetElapsedTimef();
      return;
    }

  } else { // check for singleplayer winning condition

    // TODO: define the singleplayer game
    printf("Singleplayer game not done yet");
    gameWasWon = true;
    timeGameWasWon = ofGetElapsedTimef();
    return;
  }
}

// ------------------------------------------------------------------
void PlayingGameState::spawnRandomElements() {
  float elapsed = ofGetElapsedTimef() - timeStarted;
  float tillEndOfWorldNorm = (300 - elapsed) / 300;
  
  // spawn foods, releasing less and less frequently as we approach death zone
  if (ofRandomuf() < SPAWN_FOOD_PROBABILITY * tillEndOfWorldNorm) {
    CreatureWorld::getWorld()->spawnFood();
  }
  
  // spawn rogues, releasing more and more frequently as we approach death zone
  if (ofRandomuf() < SPAWN_ROGUE_PROBABILITY * (1 - tillEndOfWorldNorm)) {
    Creature* creature = 
    CreatureWorld::getWorld()->spawnCreature(roguePlayer,
                                             100 * sqrt(ofRandomuf()),
                                             100 * sqrt(ofRandomuf()),
                                             100 * sqrt(ofRandomuf()));
    float sideProb = ofRandomuf();
    if (sideProb < 0.25) { // LEFT side
      creature->x = -100;
      creature->y = ofRandomuf() * (ofGetHeight() - 200);
    } else if (sideProb < 0.75) { // TOP side
      creature->x = ofRandomuf() * ofGetWidth();
      creature->y = -100;
    } else { // RIGHT side
      creature->x = ofGetWidth() + 100;
      creature->y = ofRandomuf() * (ofGetHeight() - 200);
    }
    creature->unleash();
  }
}

