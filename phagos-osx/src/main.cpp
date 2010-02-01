
#include "ofMain.h"
#include "ofxSDL.h"
#include "phagosApp.h"

//========================================================================
int main(int argc, char*argv[]) {

  ofxSDLAppWindow window;
  
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new phagosApp);
}
