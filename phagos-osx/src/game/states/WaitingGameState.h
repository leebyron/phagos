/*
 *  WaitingGameState.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "GameStateInstance.h"

class WaitingGameState : public GameStateInstance {
public:
  
  int foundPlayers;
  float timeStarted;
  
  void setup();
  void update();
  void draw();
  void exit();
  
  void pressed(Player* player);
  void released(Player* player);
  
};
