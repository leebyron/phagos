/*
 *  Creature.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "Creature.h"

Creature::Creature() {
  verbose       = false;

  size          = 0;
  mouthSize     = 0;
  speed         = 0;

  released      = false;

  angle         = 0;
  velocity      = 0;
}

Creature::~Creature() {
  // death to creature
}

void Creature::update() {
  // called every frame by the physics engine
  setRadius(size);
}

// called manually by our code to draw
void Creature::draw() {
  if (player) {
    glColor4f(player->color.r,
              player->color.g,
              player->color.b,
              player->color.a);
  } else {
    // rogue!
    glColor4f(0.1, 0.1, 0.1, 0.5);
  }
  
  // move to critter center
  glPushMatrix();
  glTranslatef(x, y, 0);

  // draw body
  ofCircle(0, 0, size);
  
  // draw mouth
  float mouthX = cos(angle) * size;
  float mouthY = sin(angle) * size;
  ofCircle(mouthX, mouthY, size * 0.4);
  
  // draw tail
  float tailX = -mouthX;
  float tailY = -mouthY;
  ofLine(tailX, tailY, tailX * size * 0.3, tailY * size * 0.3);
  
  glPopMatrix();
}
