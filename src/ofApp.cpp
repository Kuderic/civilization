#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	game_state = GameState::PLAY_GAME;
	pause_text.load("../../resources/SEA_GARDENS.ttf", 50);

	ofBackground(ofColor::black);
	ofSetColor(ofColor::black);
	ofSetFrameRate(kFrameRate);

	Floor::LoadTextures();
	Wall::LoadTextures();
	Colonist::LoadTextures();

	//Board dimensions can be modified in board.h
	board.setup();
	//Similarly with camera dimensions.
	camera.SetBoard(&board);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (game_state == GameState::PLAY_GAME) {
		board.update();
	}

	camera.update();

	//Framerate counter
	std::stringstream stream;
	stream << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(stream.str());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::white);
	camera.draw();

	if (game_state == GameState::PAUSED) {
		ofSetColor(ofColor::black);
		pause_text.drawString("PAUSED", 200, 200);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	camera.KeyPressed(key);

	//Pause/unpause game if space pressed
	if (key == ' ') {
		switch (game_state) {
		case GameState::PAUSED:
			game_state = GameState::PLAY_GAME;
			break;

		case GameState::PLAY_GAME:
			game_state = GameState::PAUSED;
			break;
		}
	}
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
