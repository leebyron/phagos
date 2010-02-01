/*
 *  PlayingGameState.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "GameStateInstance.h"

class PlayingGameState : public GameStateInstance {
public:
  
  float timeStarted;
  
  bool gameWasWon;
  float timeGameWasWon;
  
  void setup();
  void update();
  void draw();
  void exit();
  
  void pressed(Player* player);
  void released(Player* player);
  
};
