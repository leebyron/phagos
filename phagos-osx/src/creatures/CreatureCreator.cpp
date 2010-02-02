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
#include "Creature.h"
#include "PlayerManager.h"
#include "ofxMSAShape3D.h"
#include "Image.h"
#include "CreatureWorld.h"

static GLuint outerRingImg;
static GLuint outerRingGlow;

CreatureCreator::CreatureCreator(Player* player) {
  this->player = player;

  creature = NULL;

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
  //printf("bye creature creator\n");
}

void CreatureCreator::update() {
  opacity     += CONTROLLER_ANIMATOR * (targetOpacity - opacity);
  radius      += CONTROLLER_ANIMATOR * (targetRadius - radius);
  luminocity  += CONTROLLER_ANIMATOR * (targetLuminocity - luminocity);
  
  int lastPlayer = PlayerManager::getManager()->numPlayers - 1;
  targetX = lastPlayer == 0 ? 0.5 : ((float)player->playerNum / lastPlayer);
  targetX = round(RING_RADIUS * 1.5 + targetX * (ofGetWidth() - RING_RADIUS * 3));
  player->origin.x += CONTROLLER_ANIMATOR * (targetX - player->origin.x);
  
  // if creature last made is dead, release it...
  if (creature && creature->isDead()) {
    creature->release();
    creature = NULL;
  }

  if (!(player->stillPlaying)) {
    return;
  }

  // create monster!
  if (isPressed && creature) {
    numFramesSincePress++;
    float elapsed = ofGetElapsedTimef() - timePressed;
    
    float usedOoze = MIN(player->creatureCreator->remainingOoze, OOZE_USE_RATE);
    remainingOoze -= usedOoze;
    
    switch (creature->stepsCompleted) {
      case 0:
        creature->size += usedOoze * POINTS_TO_OOZE;
        break;
      case 1:
        creature->hunger += usedOoze * POINTS_TO_OOZE;
        break;
      case 2:
        creature->speed += usedOoze * POINTS_TO_OOZE;
        break;
    }
  } else if (player->creatureCreator->remainingOoze < 1) {
    player->creatureCreator->remainingOoze =
    CLAMP(player->creatureCreator->remainingOoze + OOZE_RECOVERY_RATE, 0, 1);
  }
}

void CreatureCreator::pressed() {
  if (remainingOoze < 0.1 || !(player->stillPlaying)) {
    return;
  }

  if (!creature || creature->stepsCompleted == 3) {
    remainingOoze -= NEW_CREATURE_COST;

    // release existing last creature
    if (creature) {
      creature->release();
    }

    creature = CreatureWorld::getWorld()->spawnCreature(player, 0, 0, 0);
    creature->retain();
  }

  timePressed = ofGetElapsedTimef();
  numFramesSincePress = 0;
  isPressed = true;
}

void CreatureCreator::released() {
  if (!creature || !isPressed || !(player->stillPlaying)) {
    return;
  }

  creature->stepsCompleted++;
  isPressed = false;
  
  if (creature->stepsCompleted == 3) {
    creature->unleash();
  }
}

void CreatureCreator::draw() {
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glPushMatrix();
  glTranslatef(player->origin.x, player->origin.y, 0);
  
  // draws ring edges
  glColor4f(1, 1, 1, player->stillPlaying ? opacity : 1);
  glPushMatrix();
  glTranslatef(-128, -128, 0);
  glScalef(256, 256, 1);
  drawTexture(outerRingImg);
  glPopMatrix();
  
  // draws ring glow
  glColor4f(1, 1, 1, opacity * luminocity);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glPushMatrix();
  glTranslatef(-128, -128, 0);
  glScalef(256, 256, 1);
  drawTexture(outerRingGlow);
  glPopMatrix();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_BLEND);
  
  glPopMatrix(); // end translate

  // draw creature if we have one
  if (creature != NULL &&
      (numFramesSincePress > 0 || creature->stepsCompleted > 0)) {
    
    glEnable(GL_STENCIL_TEST);
    
    // set stencil but don't actually draw
    glStencilFunc(GL_NEVER, 0x1, 0x1);
    glStencilOp (GL_REPLACE, GL_REPLACE, GL_REPLACE);
    ofCircle(player->origin.x, player->origin.y, RING_RADIUS * 0.93);
    
    // allow drawing where we drew into the stencil
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    
    glPushMatrix();
    glTranslatef(-creature->x * CREATOR_MAGNIFICATION, -creature->y * CREATOR_MAGNIFICATION, 0);
    glScalef(1 + CREATOR_MAGNIFICATION, 1 + CREATOR_MAGNIFICATION, 1);
    
    creature->draw(opacity);
    glPopMatrix();
    
    // turn off stenciling
    glClear(GL_STENCIL_BUFFER_BIT);
    glDisable(GL_STENCIL_TEST);
  }
  
  // draw ring
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(player->origin.x, player->origin.y, 0);
  
  float ringOpacity = opacity * (0.33 + 0.5 * luminocity);
  
  if (remainingOoze < 0.1) {
    glColor4f(1, 0, 0, ringOpacity);
  } else {
    glColor4f(player->color.r,
              player->color.g,
              player->color.b,
              ringOpacity);
  }

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
