/*
 *  IntroGameState.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "GameStateInstance.h"

class IntroGameState : public GameStateInstance {
public:
  
  float timeStarted;
  
  void setup();
  void update();
  void draw();
  void exit();
  
};
