/*
 *  OpeningGameState.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "GameStateInstance.h"

class OpeningGameState : public GameStateInstance {
public:
  
  float timeStarted;
  int frameNum;
  
  void setup();
  void update();
  void draw();
  void exit();
  
};
