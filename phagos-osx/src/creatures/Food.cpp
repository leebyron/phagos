/*
 *  Food.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 2/1/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "Food.h"
#include "Creature.h"
#include "phagosConstants.h"
#include "GameManager.h"
#include "ofxMSAShape3D.h"

static bool haveShapes = false;
static ofxMSAShape3D circle;
static ofxMSAShape3D triangle;
static ofxMSAShape3D square;

static float foodHues[2] = {10, 120};

Food::Food() {
  verbose       = false;
  type          = FOOD_PARTICLE;
  setRadius(FOOD_SIZE - 2);

  state         = FOOD_INTRO;
  timeCreated   = ofGetElapsedTimef();
  drawInWorld   = true;
  angle         = 0;
  angleV        = 0.01 * ofRandomuf();

  // set type
  type = floor(ofRandom(0, FOOD_NUM_KINDS - 0.0001)); // TODO: properly weight the different types
  
  if (type == 0) {
    color.set(1,1,1,1);
  } else {
    color.setHSV(foodHues[type-1], 1, 1, 1);
  }
  
  // place randomly on stage
  moveTo(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight() - 200), 0);
  
  // for first food, make geometry
  if (!haveShapes) {
    haveShapes = true;
    float x, y;
    int n;
    
    n = 20;
    circle.begin(GL_TRIANGLE_FAN);
    circle.addVertex(0, 0, 0);
    for (int i = 0; i < n; i++) {
      x = cos(TWO_PI * i/(n-1)) * FOOD_SIZE;
      y = sin(TWO_PI * i/(n-1)) * FOOD_SIZE;
      circle.addVertex(x, y, 0);
    }
    circle.end();

    // TODO: properly draw triangles and squares
    n = 4;
    triangle.begin(GL_TRIANGLE_FAN);
    triangle.addVertex(0, 0, 0);
    for (int i = 0; i < n; i++) {
      x = cos(TWO_PI * i/(n-1)) * FOOD_SIZE;
      y = sin(TWO_PI * i/(n-1)) * FOOD_SIZE;
      triangle.addVertex(x, y, 0);
    }
    triangle.end();
    
    n = 5;
    square.begin(GL_TRIANGLE_FAN);
    square.addVertex(0, 0, 0);
    for (int i = 0; i < n; i++) {
      x = cos(-TWO_PI * i/(n-1)) * FOOD_SIZE;
      y = sin(-TWO_PI * i/(n-1)) * FOOD_SIZE;
      square.addVertex(x, y, 0);
    }
    square.end();
  }
}

Food::~Food() {
  //printf("bye food!\n");
}

bool Food::isEdible() {
  return state == FOOD_EDIBLE;
}

void Food::eatenBy(Creature* creature) {
  state           = FOOD_EATEN;
  locationEaten   = *creature;
  timeEaten       = ofGetElapsedTimef();
  makeFixed();
  
  // give them POWER
  switch (type) {
    case FOOD_HEALTH:
      creature->size    += FOOD_SIZE_POINTS;
      creature->hunger  += FOOD_HUNGER_POINTS;
      creature->speed   += FOOD_SPEED_POINTS;
      break;
    case FOOD_RAGE:
      break;
    case FOOD_PROTECT:
      break;
  }
}

void Food::releasedFrom(Creature* creature) {
  state           = FOOD_RELEASED;
  timeReleased    = ofGetElapsedTimef();
  drawInWorld     = true;

  // set new position and blow up
  makeFree();
  moveTo(*creature);
  addVelocity(ofRandomf() * FOOD_RELEASED_SPEED,
              ofRandomf() * FOOD_RELEASED_SPEED, 0);
}

void Food::update() {
  if (state == FOOD_EATEN) return;
  
  // add a slight velocity // TODO: improve or remove when world has fluid movements
  addVelocity(ofRandomf() * 0.1,
              ofRandomf() * 0.1, 0);

  // update rotation based on velocity
  ofPoint v = getVelocity();
  angleV += msaLength(v) * (v.x < 0 ? 1 : -1) * FOOD_SPINNINESS;
  angleV *= 0.97;
  angle += angleV;
  
  // todo why does this break rotation?
/*  if (angle > TWO_PI) {
    angle -= TWO_PI;
  }
  if (angle < TWO_PI) {
    angle += TWO_PI;
  }*/
}

void Food::draw() {
  if (!drawInWorld) return;
  
  float elapsed;
  
  switch (state) {
    case FOOD_INTRO:
      // draw the food fading in
      
      elapsed = sqAni((ofGetElapsedTimef() - timeCreated) * 0.5);
      if (elapsed >= 1) {
        // if its fully faded in, then its eatable!
        state = FOOD_EDIBLE;
      }
      glPushMatrix();
      glTranslatef(x, y, 0);
      glRotatef(angle, 0, 0, 1);
      glScalef(1 + (1 - elapsed)*0.5,
               1 + (1 - elapsed)*0.5, 1);
      drawFoodAtOrigin(elapsed);
      glPopMatrix();
      
      break;

    case FOOD_EDIBLE:
      // draw the food as normal
      glPushMatrix();
      glTranslatef(x, y, 0);
      glRotatef(angle, 0, 0, 1);
      drawFoodAtOrigin(1);
      glPopMatrix();
      
      break;

    case FOOD_EATEN:
      // draw a ripple outwards if its been eaten
      elapsed = CLAMP((ofGetElapsedTimef() - timeEaten) / TIME_FOR_FOOD_RIPPLE, 0, 1);
      if (elapsed > 1) {
        // if the ring is gone, then don't draw at all
        drawInWorld = false;
      }
      glPushMatrix();
      glTranslatef(locationEaten.x, locationEaten.y, 0);
      glScalef(1 + SIZE_OF_FOOD_RIPPLE * SQ(elapsed),
               1 + SIZE_OF_FOOD_RIPPLE * SQ(elapsed), 1);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
      glColor4f(color.r, color.g, color.b, 1-sqrt(elapsed));
      GameManager::getManager()->ring->draw();
      glDisable(GL_BLEND);
      glPopMatrix();
      
      break;
    
    case FOOD_RELEASED:
      // draw the food as normal
      glPushMatrix();
      glTranslatef(x, y, 0);
      glRotatef(angle, 0, 0, 1);
      drawFoodAtOrigin(1);
      glPopMatrix();

      elapsed = ofGetElapsedTimef() - timeReleased;
      if (elapsed > 1) {
        // if its fully released in, then its eatable!
        state = FOOD_EDIBLE;
      }

      break;
  }
}

void Food::drawFoodAtOrigin(float opacity) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  opacity *= 0.6;
  glColor4f(color.r, color.g, color.b, opacity);

  switch (type) {
    case FOOD_HEALTH:
      circle.draw();
      break;
    case FOOD_RAGE:
      square.draw();
      break;
    case FOOD_PROTECT:
      triangle.draw();
      break;
  }

  glDisable(GL_BLEND);
}
