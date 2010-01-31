/*
 *  phagosApp.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxSDL.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "CreatureWorld.h" 

class phagosApp : public ofxSDLApp {
public:

  GameManager*    gameManager;
  PlayerManager*  playerManager;
  CreatureWorld*  world;

  void setup();
  void update();
  void draw();
  void exit();

  void keyPressed(int key);
  void keyReleased(int key);
  void joyButtonPressed(int device, int button);
  void joyButtonReleased(int device, int button);
  void windowResized(int w, int h);

  float counter;
  bool	bSmooth;
};
