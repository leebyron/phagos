/*
 *  phagosConstants.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 1/31/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "phagosConstants.h"
#include "ofMain.h"

float sqAni(float x) {
  return (1 - cos(CLAMP(x, 0, 1) * PI)) * 0.5;
}

