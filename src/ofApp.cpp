#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(ofColor::black);
	ofSetFrameRate(60);

	Floor::LoadTextures();
	Wall::LoadTextures();
	Colonist::LoadTextures();

	//Board dimensions can be modified in board.h
	board.setup();
	//Similarly with camera dimensions.
	camera.SetBoard(&board);
}

//--------------------------------------------------------------
void ofApp::update(){
	board.update();
	camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	camera.KeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	camera.KeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofPoint tile_pos = camera.GetTilePosition(x, y);
	board.TileClicked(tile_pos);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	ofPoint tile_pos = camera.GetTilePosition(x, y);
	board.TileClicked(tile_pos);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
