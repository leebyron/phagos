/*
 *  CreatureWorld.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once
#include "Creature.h"
#include "Food.h"
#include "ofxMSAPhysics.h"
#include "EdgesForceField.h"
#include "CollisionForceField.h"

class CreatureWorld {
public:

  static CreatureWorld* getWorld();
  CreatureWorld();
  ~CreatureWorld();

  ofxMSAPhysics*  physics;
  list<Creature*> creatures;
  list<Food*>     foods;

  EdgesForceField* edgesForceField;
  CollisionForceField* collisionForceField;

  void resetWorld();
  void updateWorld();
  Food* spawnFood();
  Creature* spawnCreature(Player* player,
                          float size,
                          float hunger,
                          float speed);
};
