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
#include "phagosConstants.h"

class phagosApp : public ofxSDLApp {//public ofBaseApp {
public:

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
};
