/*
 *  Food.h
 *  Phagos
 *
 *  Created by Lee Byron on 2/1/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "ofxMSAPhysics.h"
#include "ofxMSAUtils.h"

// the state of this food
#define FOOD_INTRO    0
#define FOOD_EDIBLE   1
#define FOOD_EATEN    2
#define FOOD_RELEASED 3

// the type of food
#define FOOD_NUM_KINDS 3
#define FOOD_HEALTH    0
#define FOOD_RAGE      1
#define FOOD_PROTECT   2

#define FOOD_PARTICLE 0x321

class Creature;

class Food : public ofxMSAParticle {
public:

  Food();
  ~Food();

  int state;
  int type;
  ofPoint locationEaten;
  msaColor color;
  float timeCreated;
  float timeEaten;
  float timeReleased;
  bool drawInWorld;
  
  float angle;
  float angleV;
  
  bool isEdible();
  void eatenBy(Creature* creature);
  void releasedFrom(Creature* creature);
  
  void update();
  void draw();
  void drawFoodAtOrigin(float opacity);
  
};