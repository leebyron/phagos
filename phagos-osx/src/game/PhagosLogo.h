/*
 *  PhagosLogo.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/31/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#include "ofMain.h"

class PhagosLogo {
public:
  
  static PhagosLogo* getLogo();
  PhagosLogo();
  ~PhagosLogo();

  GLuint images[60];
  
  float offset[12];
  float frequency[12];

  void update();
  void draw(float alpha);
  
};
