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
  size          = 0;
  mouthSize     = 0;
  speed         = 0;
  released      = false;
}

Creature::~Creature() {
  // death to creature
}
