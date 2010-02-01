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
#include "ofxMSAPhysics.h"
#include "EdgesForceField.h"
#include "CollisionForceField.h"

class CreatureWorld {
public:

  static CreatureWorld* getWorld();
  CreatureWorld();
  ~CreatureWorld();

  ofxMSAPhysics*  physics;
  vector<Creature*> creatures;
  
  EdgesForceField* edgesForceField;
  CollisionForceField* collisionForceField;

  void resetWorld();
  void updateWorld();
  Creature* spawnCreature(Player* player,
                          float size,
                          float hunger,
                          float speed);

};
