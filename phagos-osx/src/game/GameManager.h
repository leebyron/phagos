/*
 *  GameManager.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "GameStateInstance.h"
#include "ofxMSAShape3D.h"

typedef unsigned int GameState;
static const GameState OPENING_SEQUENCE     = 0x1;  // Credit roll, played once when game is launched
static const GameState INTRO_SEQUENCE       = 0x2;  // Played right before actively looking for gamers
static const GameState WAITING_FOR_PLAYERS  = 0x4;  // Endless loop looking for first player
static const GameState PLAYING_GAME         = 0x8; // Active gameplay
static const GameState GAME_OVER            = 0x16; // Played right after the game ends

class GameManager {
public:

  static GameManager* getManager();
  GameManager();
  ~GameManager();

  GameState currentState;
  GameStateInstance* currentStateInstance;
  
  GLuint backgroundImage;
  ofxMSAShape3D* ring;

  void update();
  void draw();
  void pressed(Player* player);
  void released(Player* player);

  void setState(GameState newState);
  bool isAcceptingNewPlayers();
  
};
