#include "ofMain.h"
#include "ofApp.h"

//========================================================================

//If configuration is UnitTesting don't run main method
#ifndef UNIT_TESTING

int main( ) {
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	ofSetFrameRate(30);

	std::ofstream output_file;
	output_file.open("model.txt");
	output_file << "asdf";
	output_file.close();

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
#endif