#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    //desk top:1524,868
    //lap top:1824,1068
    ofSetupOpenGL(1524,868, OF_WINDOW);// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
