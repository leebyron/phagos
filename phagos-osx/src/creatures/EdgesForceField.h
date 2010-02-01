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
  
  inline void update(ofxMSAParticle* p) {    
		float restLength = radius - p->getRadius();
		ofPoint delta = (*p) - (center);
    
    // transform oval
    delta.y *= 2.0;
    float force;

		float deltaLength2 = msaLengthSquared(delta);
		if (deltaLength2 < restLength * restLength) {
    } else {
      float deltaLength = sqrt(deltaLength2); //msaFastInvSquareRoot(deltaLength2);	// TODO: fast approximation of square root (1st order Taylor-expansion at a neighborhood of the rest length r (one Newton-Raphson iteration with initial guess r))
      force = (deltaLength - restLength) / (deltaLength);
    }
    
    // nudge towards center
    force += 0.1;
    
    // un-transform oval
    delta.y *= 0.5;
    
		*p += delta * (1 * -force) * EDGE_FIELD_STRENGTH;
  }
  
};
