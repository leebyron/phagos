/*
 *  CollisionForceField.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/31/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "CollisionForceField.h"
#include "CreatureWorld.h"
#include "Creature.h"
#include "phagosConstants.h"

CollisionForceField::CollisionForceField() {
  world = NULL;
}

void CollisionForceField::update() {
  if (world == NULL) {
    world = CreatureWorld::getWorld();
  }
  
  // O(n^2) loop goes here, do some smart ass shit.
  
  list<Creature*>::iterator it;
  list<Creature*>::iterator jt;
  for (it = world->creatures.begin(); it != world->creatures.end(); ++it) {
    _a = *it;
    rA = _a->getRadius();
    for (jt = it; jt != world->creatures.end(); ++jt) {
      _b = *jt;
      if (_a == _b) continue;

/*  
  
  n = world->creatures.size();
  for (int i = 0; i < n; i++) {
    _a = world->creatures[i];
    rA = _a->getRadius();
    for (int j = i + 1; j < n; j++) {
      _b = world->creatures[j];*/
      rB = _b->getRadius();
      restLength = rA + rB;
      delta = (*_b) - (*_a);
      
      // throw out clear ones
      if (fabs(delta.x) > restLength) continue;
      if (fabs(delta.y) > restLength) continue;
      deltaLength2 = msaLengthSquared(delta);
      if (deltaLength2 > restLength * restLength) continue;
      
      deltaLength = sqrtf(deltaLength2); // TODO: fast approximation of square root (1st order Taylor-expansion at a neighborhood of the rest length r (one Newton-Raphson iteration with initial guess r))
      force = CREATURE_SQUISHINESS * (deltaLength - restLength) / (deltaLength * (_a->getInvMass() + _b->getInvMass()));
      
      if (!_a->isFixed()) *_a += delta * (_a->getInvMass() * force);
      if (!_b->isFixed()) *_b -= delta * (_b->getInvMass() * force);
    }
  }
}
