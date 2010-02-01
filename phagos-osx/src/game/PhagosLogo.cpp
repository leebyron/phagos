/*
 *  PhagosLogo.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/31/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "PhagosLogo.h"
#include "Image.h"
#include "phagosConstants.h"

static PhagosLogo* instance = NULL;

static int offsetX[12] = {121,125,258,258,399,399,528,564,665,691,807,806};
static int offsetY[12] = {226,260,230,260,229,260,228,261,227,252,256,230};

PhagosLogo* PhagosLogo::getLogo() {
  if (instance == NULL) {
    instance = new PhagosLogo();
  }
  return instance;
}

PhagosLogo::PhagosLogo() {
  string phagos = "phagos";
  string file;
  int index;
  string letter;
  for (int i = 0; i < 6; i++) {
    letter = phagos.substr(i, 1);
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 5; k++) {
        file = "logo/";
        file += letter + "-" + ofToString(j+1) + "_000" + ofToString(k) + ".png";
        index = i * 10 + j * 5 + k;
        images[index] = loadTexture(file, GL_BGRA);
      }
    }
  }

  reset();
}

PhagosLogo::~PhagosLogo() {
}

void PhagosLogo::reset() {
  for (int i = 0; i < 12; i++) {
    offset[i] = ofRandom(0, 3);
    frequency[i] = 0.3 + ofRandomuf();
  }
}

void PhagosLogo::update() {
  for (int i = 0; i < 12; i++) {
    offset[i] += frequency[i] * 0.03;
  }
}

void PhagosLogo::draw(float alpha) {
  int blurLevel = 4;
  float zLevel = 0;
  float fadeLevel = 0;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  for (int i = 0; i < 12; i++) {
    
    fadeLevel = sqAni(offset[i] * 0.35 - 1.3);
    glColor4f(1,1,1,fadeLevel*alpha);

    zLevel = sin(offset[i]);
    blurLevel = 4 - floor(fabs(zLevel) * 5);
    blurLevel = CLAMP(blurLevel, 0, 4);

    glPushMatrix();
    glTranslatef(offsetX[i], offsetY[i], zLevel * 5);
    glScalef(128, 128, 1);
    drawTexture(images[i * 5 + blurLevel]);
    glPopMatrix();
  }

  glDisable(GL_BLEND);
}
