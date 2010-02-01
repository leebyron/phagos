/*
 *  EdgesForceField.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/31/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once

#import "ofxMSAPhysics.h"
#import "phagosConstants.h"

class EdgesForceField : public ofxMSAParticleUpdater {
public:
  
  inline EdgesForceField() {
    width     = ofGetWidth() * 0.5;
    height    = (ofGetHeight() - 200) * 0.5;
    center.x  = ofGetWidth() * 0.5;
    center.y  = (ofGetHeight() - 200) * 0.5;
    radius    = ofGetWidth() * 0.48;
  }
  
  ofPoint center;
  float width;
  float height;
  float radius;
  
  float restLength;
  ofPoint deltaDistance;
  float deltaLength2;
  float deltaLength;
  float force;
  
  inline void update(ofxMSAParticle* p) {    
		restLength = radius - p->getRadius();
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
    force += 0.25;

    // un-transform oval
    deltaDistance.y *= 0.5;
    
		*p += deltaDistance * (1 * -force) * EDGE_FIELD_STRENGTH;
  }
  
};
