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
  
  void update(ofxMSAParticle* p);

};
