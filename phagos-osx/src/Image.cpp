/*
 *  Image.cpp
 *  _Fireflies
 *
 *  Created by Lee Byron on 10/9/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.h"

Image::Image(string file) {
  FreeImage_Initialise();
  
  const char* fileString = ofToDataPath(file).c_str();
	bmp = 0;
	pixels = 0;
	//----------------------------- find the format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(fileString, 0);
	if(fif == FIF_UNKNOWN) {
		// or guess via filename
		fif = FreeImage_GetFIFFromFilename(fileString);
	}
	if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
		bmp = FreeImage_Load(fif, fileString, 0);
	} else {
    printf("badness\n");
  }
	
	if (!bmp) {
		printf("Error loading image %s\n", fileString);
		return;
	}
	
	//-----------------------------
	width		= FreeImage_GetWidth(bmp);
	height 		= FreeImage_GetHeight(bmp);
	bpp 		= FreeImage_GetBPP(bmp);	
	
	int byteCount = bpp / 8;		// bytes ber pixel (not bits per pixel)
	pixels = new unsigned char[width*height*byteCount];	//allocate that memory for the image (contiguously)
	FreeImage_ConvertToRawBits(pixels, bmp, width*byteCount, bpp, FI_RGBA_RED_MASK,FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);  // get bits
}

Image::~Image() {
	if (bmp) {
		FreeImage_Unload(bmp);
	}
	if (pixels) {
		delete [] pixels;
	}
}

GLuint loadTexture(string file, GLint type) {
	Image *img = new Image(file);
	
	GLuint textureName;
	
	glGenTextures(1, &textureName);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	/*
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/
	
    // when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	// build our texture mipmaps
  if (type == GL_BGRA) {
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, img->width, img->height, GL_BGRA, GL_UNSIGNED_BYTE, img->pixels );
  } else if (type == GL_BGR) {
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, img->width, img->height, GL_BGR, GL_UNSIGNED_BYTE, img->pixels );
  } else if (type == GL_RGB) {
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, img->width, img->height, GL_RGB, GL_UNSIGNED_BYTE, img->pixels );
  }
	
	/*
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ofNextPow2(img->width), ofNextPow2(img->height), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, 0);  // init to black...
	
	GLint prevAlignment;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevAlignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,img->width,img->height,type,GL_UNSIGNED_BYTE,img->pixels);
	glPixelStorei(GL_UNPACK_ALIGNMENT, prevAlignment);
	glDisable(GL_TEXTURE_2D);
	 */
	
	// delete what we dont need!
	delete img;
	
	return textureName;
}

void drawTexture(GLuint tex) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 0);    glVertex2f(0, 0);
	glTexCoord2f(1, 0);    glVertex2f(1, 0);
	glTexCoord2f(0, 1);    glVertex2f(0, 1);
	glTexCoord2f(1, 1);    glVertex2f(1, 1);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}

