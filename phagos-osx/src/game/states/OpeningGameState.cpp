/*
 *  OpeningGameState.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "OpeningGameState.h"
#include "ofMain.h"
#include "GameManager.h"
#include "Image.h"
#include "phagosConstants.h"

static GLuint scientists;
static GLuint skeletists;
static GLuint lab;

void OpeningGameState::setup() {
  printf("opening game state setup\n");
  
  timeStarted = ofGetElapsedTimef();
  frameNum = 0;

  ofBackground(0, 0, 0);
  scientists = loadTexture("science/scientists.png", GL_BGR);
  skeletists = loadTexture("science/skeletists.png", GL_BGR);
  lab        = loadTexture("science/lab.png",        GL_BGR);
}

void OpeningGameState::update() {  
  float elapsed = ofGetElapsedTimef() - timeStarted;
  if (elapsed > 10.0) {
    manager->setState(INTRO_SEQUENCE);
  }
  frameNum++;
}

void OpeningGameState::draw() {
  float elapsed = ofGetElapsedTimef() - timeStarted;
  
  if (elapsed < 1.0) {
    return;
  }
  
  float fadeSci = 1;
  if (elapsed < 2.0) {
    fadeSci = sqAni(elapsed - 1);
  } else if (elapsed > 5.5) {
    fadeSci = sqAni(9.5 - elapsed);
  }
  glColor4f(fadeSci, fadeSci, fadeSci, 1);

  glPushMatrix();
  glScalef(1024, 1024, 1);
  if (frameNum == 209 || frameNum == 251 || frameNum == 256 || frameNum == 278 ||
      frameNum == 281 || frameNum == 283 || frameNum == 287) {
    ofRect(0, 0, 1, 1);
  } else if ((frameNum >= 210 && frameNum <= 214) ||
      frameNum == 246 || 
      (frameNum >= 252 && frameNum <= 260) ||
      (frameNum >= 275 && frameNum <= 291)) {
    drawTexture(skeletists);
  } else if (frameNum < 350) {
    drawTexture(scientists);
  }
  glPopMatrix();
  
  if (frameNum >= 420) {
    glPushMatrix();
    glTranslatef(ofGetWidth()*0.5, ofGetHeight()*0.5, 0);
    glScalef(512, 128, 1);
    glTranslatef(-0.5, -0.5, 1);
    drawTexture(lab);
    glPopMatrix();
  }
}

void OpeningGameState::exit() {
  printf("opening game state teardown\n");
}
