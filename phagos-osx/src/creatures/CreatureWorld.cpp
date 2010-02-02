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
  // remove all creatures
  list<Creature*>::iterator creatureIter;
  Creature* creature;
  for (creatureIter = creatures.begin(); creatureIter != creatures.end(); ++creatureIter) {
    creature = *creatureIter;
    creature->release();
  }
  creatures.clear();

  // remove all foods
  list<Food*>::iterator foodIter;
  Food* food;
  for (foodIter = foods.begin(); foodIter != foods.end(); ++foodIter) {
    food = *foodIter;
    //food->release();
  }
  foods.clear();

  // clear physics
  physics->clear();
}

void CreatureWorld::updateWorld() {
  physics->update(1);

  // remove creatures that are long since dead!
  list<Creature*>::iterator it = creatures.begin();
  Creature* creature;
  while (it != creatures.end()) {
    creature = *it;
    if (creature->isDead()) {
      it = creatures.erase(it);
      creature->release();
    } else {
      it++;
    }
  }
}

Food* CreatureWorld::spawnFood() {
  Food* food = new Food();
  foods.push_back(food);
  physics->addParticle(food);
  food->release();
}

Creature* CreatureWorld::spawnCreature(Player* player,
                                       float size,
                                       float hunger,
                                       float speed) {
  Creature* spawned = new Creature();

  spawned->player   = player;
  spawned->size     = size;
  spawned->hunger   = hunger;
  spawned->speed    = speed;
  
  spawned->setMass(1);
  // TODO: move if player is rogue
  spawned->moveTo(player->origin);

  // count this as a reference increment
  spawned->retain();
  creatures.push_back(spawned);

  // add and dereference
  physics->addParticle(spawned);
  spawned->release();

  return spawned;
}