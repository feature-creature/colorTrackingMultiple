#include "ofMain.h"
#include "ofApp.h"

/*
 * linux w/ ps2 camera
 * $ sudo apt-get install v4l2ucp
 * $ v4l2ucp
 * 
 * turn off auto white balance and auto exposure
 * for more consistent results
 * also vertical & horizontal flip of camera feed
 * 
 */

//========================================================================
int main( ){
	ofSetupOpenGL(640,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
