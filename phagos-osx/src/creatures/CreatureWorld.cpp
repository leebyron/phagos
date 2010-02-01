/*
 *  CreatureWorld.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "CreatureWorld.h"

static CreatureWorld* instance = NULL;

CreatureWorld* CreatureWorld::getWorld() {
  if (instance == NULL) {
    instance = new CreatureWorld();
  }
  return instance;
}

CreatureWorld::CreatureWorld() {
  physics = new ofxMSAPhysics();
  physics->clear();
  
  float w = ofGetWidth();
  float h = ofGetHeight();
  physics->setWorldSize(ofPoint(-w/2, -h/2, -w/2), ofPoint(w * 1.5, h * 1.5, w/2));
  
  physics->setDrag(0.975);
  physics->disableCollision();
  physics->set2D(true);

  edgesForceField = new EdgesForceField();
  physics->addUpdater(edgesForceField);

  collisionForceField = new CollisionForceField();
  physics->addWorldUpdater(collisionForceField);

}

CreatureWorld::~CreatureWorld() {
  delete physics;
}

void CreatureWorld::resetWorld() {
  // remove all critters
  list<Creature*>::iterator it;
  Creature* creature;
  for (it=creatures.begin(); it!=creatures.end(); ++it) {
    creature = *it;
    creature->release();
  }
  creatures.clear();
  physics->clear();
}

void CreatureWorld::updateWorld() {
  physics->update(1);

  // remove creatures that are long since dead!
  list<Creature*>::iterator it;
  Creature* creature;
  for (it=creatures.begin(); it!=creatures.end(); ++it) {
    creature = *it;
    if (creature->isDead()) {
      creature->release();
      creatures.erase(it);
    }
  }
}

Creature* CreatureWorld::spawnCreature(Player* player,
                                       float size,
                                       float hunger,
                                       float speed) {
  Creature* spawned = new Creature();

  spawned->player       = player;
  spawned->size         = size;
  spawned->hunger    = hunger;
  spawned->speed        = speed;
  
  spawned->setMass(1);
  // TODO: move if player is rogue
  spawned->moveTo(player->origin);

  // count this as a reference increment
  spawned->retain();
  creatures.push_back(spawned);
  
  physics->addParticle(spawned);
  
  return spawned;
}