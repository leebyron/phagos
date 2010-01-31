/*
 *  GameManager.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#import "GameStateInstance.h"

typedef unsigned int GameState;
static const GameState INITIAL_STATE        = 0x0;
static const GameState OPENING_SEQUENCE     = 0x1;  // Credit roll, played once when game is launched
static const GameState INTRO_SEQUENCE       = 0x2;  // Played right before actively looking for gamers
static const GameState WAITING_FOR_PLAYERS  = 0x4;  // Endless loop looking for first player
static const GameState PREPARING_GAME       = 0x16; // Played right before game play begins
static const GameState PLAYING_GAME         = 0x32; // Active gameplay
static const GameState GAME_OVER            = 0x64; // Played right after the game ends

class GameManager {
public:

  static GameManager* getManager();
  GameManager();
  ~GameManager();

  GameState currentState;
  GameStateInstance* currentStateInstance;

  void update();
  void draw();
  void pressed(Player* player);
  void released(Player* player);

  void setState(GameState newState);
  bool isAcceptingNewPlayers();
  
};
