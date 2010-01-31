/*
 *  CreatureCreator.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "CreatureCreator.h"
#include "phagosConstants.h"
#include "Player.h"
#include "PlayerManager.h"
#include "ofxMSAShape3D.h"
#include "Image.h"

static GLuint outerRingImg;
static GLuint outerRingGlow;

CreatureCreator::CreatureCreator(Player* player) {
  this->player = player;

  remainingOoze = 1.0;
  luminocity    = 0.0;
  radius        = 2.0;
  opacity       = 0.0;

  targetLuminocity = 0.0;
  targetRadius     = 1.0;
  targetOpacity    = 1.0;

  outerRingImg = loadTexture("images/creator-ring.png", GL_BGRA);
  outerRingGlow = loadTexture("images/ring-glow.png", GL_BGRA);
}

CreatureCreator::~CreatureCreator() {
}

void CreatureCreator::update() {
  opacity     += CONTROLLER_ANIMATOR * (targetOpacity - opacity);
  radius      += CONTROLLER_ANIMATOR * (targetRadius - radius);
  luminocity  += CONTROLLER_ANIMATOR * (targetLuminocity - luminocity);
  
  int lastPlayer = PlayerManager::getManager()->numPlayers - 1;
  targetX = lastPlayer == 0 ? 0.5 : ((float)player->playerNum / lastPlayer);
  targetX = round(RING_RADIUS * 1.5 + targetX * (ofGetWidth() - RING_RADIUS * 3));
  player->origin.x += CONTROLLER_ANIMATOR * (targetX - player->origin.x);
}

void CreatureCreator::draw() {
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glPushMatrix();
  glTranslatef(player->origin.x, player->origin.y, 0);
  
  // draws it here!
  glColor4f(1, 1, 1, 1);
  glPushMatrix();
  glTranslatef(-128, -128, 0);
  glScalef(256, 256, 1);
  drawTexture(outerRingImg);
  glPopMatrix();
  
  // draws it here!
  glColor4f(1, 1, 1, luminocity);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glPushMatrix();
  glTranslatef(-128, -128, 0);
  glScalef(256, 256, 1);
  drawTexture(outerRingGlow);
  glPopMatrix();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // draw ring
  float ringOpacity = opacity * (0.33 + 0.5 * luminocity);
  glColor4f(player->color.r,
            player->color.g,
            player->color.b,
            ringOpacity);

  ofxMSAShape3D ring;
  ring.begin(GL_TRIANGLE_STRIP);
  float x,y,a;
  float outerR = radius * RING_RADIUS;
  float innerR = outerR * 0.93;
  float totalA = TWO_PI * remainingOoze / (RING_RESOLUTION - 1);
  for (int i = 0; i < RING_RESOLUTION; i++) {
    a = totalA * i;
    x = cos(a - HALF_PI);
    y = sin(a - HALF_PI);

    ring.addVertex(x * outerR, y * outerR);
    ring.addVertex(x * innerR, y * innerR);
  }
  ring.end();
  ring.draw();
  
  glPopMatrix(); // end translate

  glDisable(GL_BLEND);
}
