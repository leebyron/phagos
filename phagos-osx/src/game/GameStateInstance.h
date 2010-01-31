/*
 *  GameStateInstance.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "ofxObjCPointer.h"

class GameManager;

class GameStateInstance : public ofxObjCPointer {
public:

  GameManager* manager;
  
  virtual void setup() {};
  virtual void update() {};
  virtual void draw() {};
  virtual void exit() {};
  
};
