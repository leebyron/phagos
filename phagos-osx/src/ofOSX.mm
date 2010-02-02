//
//  ofOSX.mm
//  _Fireflies
//
//  Created by Lee Byron on 11/14/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "ofOSX.h"
#import <Cocoa/Cocoa.h>

string getResourcesPath() {
	string rPath( [[[NSBundle mainBundle] resourcePath] UTF8String] );
	return rPath;
}