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
#include "CreatureWorld.h"
#include "Creature.h"

void PlayingGameState::setup() {
  printf("play game state setup\n");
  
  CreatureWorld::getWorld()->resetWorld();
  
  timeStarted = ofGetElapsedTimef();
  
  ofBackground(0,0,0);
}

void PlayingGameState::update() {
  
  float elapsed = ofGetElapsedTimef() - timeStarted;
  
  if (elapsed > 300) { // TODO: what else actually triggers this?
    manager->setState(GAME_OVER);
  }

  CreatureWorld::getWorld()->updateWorld();
}

void PlayingGameState::draw() {
  ofSetColor(0x6600FF);
  
  CreatureWorld* world = CreatureWorld::getWorld();
  Creature* creature;
  
  // draw all of the creatures on the screen please
  for (int i = 0; i < world->creatures.size(); i++) {
    world->creatures[i]->draw();
  }

  string state = "playing state";
	ofDrawBitmapString(state, 140, 220);
}

void PlayingGameState::exit() {
  printf("play game state teardown\n");
}

void PlayingGameState::pressed(Player* player) {
  //printf("pressed by %i\n", player->playerNum);
}

void PlayingGameState::released(Player* player) {
  //printf("released by %i\n", player->playerNum);

  Creature* creature = CreatureWorld::getWorld()->spawnCreature(player, 10, 10, 10);
  creature->addVelocity(ofRandomf(), ofRandomf(), 0);
}
