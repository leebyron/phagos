/*
 *  Image.h
 *  _Fireflies
 *
 *  Created by Lee Byron on 10/9/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _IMAGE_H
#define _IMAGE_H

#include "ofUtils.h"
#include <string>
#include "FreeImage.h"

class Image {
public:
	Image(string file);
	~Image();

	FIBITMAP *      bmp;
	int             width;
	int             height;
	int             bpp;
	unsigned char * pixels;
};

// also have some c functions for making and drawing textures
GLuint loadTexture(string file, GLint type);
//GLuint loadTexture(string file){ loadTexture(file, GL_BGRA); }
void   drawTexture(GLuint tex);

#endif
