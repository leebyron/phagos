/*
 *  EdgesForceField.cpp
 *  Phagos
 *
 *  Created by Lee Byron on 2/1/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#import "EdgesForceField.h"
#import "GameManager.h"

void EdgesForceField::update(ofxMSAParticle* p) {
  bool inGame = GameManager::getManager()->currentState == PLAYING_GAME;
  
  restLength = radius - p->getRadius();
  
  if (!inGame) {
    restLength *= 2;
  }
  
  deltaDistance = (*p) - (center);
  
  // transform oval
  deltaDistance.y *= 2.0;
  
  force = 0;
  deltaLength2 = msaLengthSquared(deltaDistance);
  if (deltaLength2 < restLength * restLength) {
    ;
  } else {
    deltaLength = sqrt(deltaLength2); //msaFastInvSquareRoot(deltaLength2);	// TODO: fast approximation of square root (1st order Taylor-expansion at a neighborhood of the rest length r (one Newton-Raphson iteration with initial guess r))
    force = (deltaLength - restLength) / (deltaLength);
  }
  
  // nudge towards center
  if (inGame) {
    force += 0.20;
  } else {
    force += 0.05;
  }
  
  // un-transform oval
  deltaDistance.y *= 0.5;
  
  *p += deltaDistance * (1 * -force) * EDGE_FIELD_STRENGTH;
}
