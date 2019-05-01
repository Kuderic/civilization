#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	game_state = GameState::PLAY_GAME;
	click_state = ClickState::NONE;

	ofBackground(ofColor::black);
	ofSetColor(ofColor::black);
	ofSetFrameRate(kFrameRate);

	Floor::LoadTextures();
	Wall::LoadTextures();
	Colonist::LoadTextures();
	pause_text.load("../../resources/SEA_GARDENS.ttf", 50);
	interface_text.load("../../resources/SEA_GARDENS.ttf", 20);

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
	ofSetColor(ofColor::white); //	White color needed to draw images normally
	camera.draw();

	if (game_state == GameState::PAUSED) {
		ofSetColor(ofColor::black);
		pause_text.drawString("PAUSED", 300, 300);
	}

	//Draw interface
	ofSetColor(ofColor::black);
	interface_text.drawString("'w' | Create Wall", 10, 30);
	interface_text.drawString("'d' | Delete Wall", 10, 60);
	interface_text.drawString("'m' | Move Dog", 10, 90);

	//Draw currently selected action in yellow
	ofSetColor(ofColor::yellow);
	switch (click_state) {
	case ClickState::CREATE_WALL:
		interface_text.drawString("'w' | Create Wall", 10, 30);
		break;

	case ClickState::DELETE_WALL:
		interface_text.drawString("'d' | Delete Wall", 10, 60);
		break;

	case ClickState::MOVE_COLONIST:
		interface_text.drawString("'m' | Move Dog", 10, 90);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	camera.KeyPressed(key);

	//Pause/unpause game if space pressed
	switch (key) {
	case ' ':
		switch (game_state) {
		case GameState::PAUSED:
			game_state = GameState::PLAY_GAME;
			break;

		case GameState::PLAY_GAME:
			game_state = GameState::PAUSED;
			break;
		}
	}

	UpdateClickState(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	camera.KeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	ParseBoardClick(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ParseBoardClick(x, y, button);
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

void ofApp::UpdateClickState(int key) {
	switch (key) {
	case 'w':
		if (click_state == ClickState::CREATE_WALL) {
			click_state = ClickState::NONE;
		}
		else {
			click_state = ClickState::CREATE_WALL;
		}
		break;

	case 'd':
		if (click_state == ClickState::DELETE_WALL) {
			click_state = ClickState::NONE;
		}
		else {
			click_state = ClickState::DELETE_WALL;
		}
		break;

	case 'm':
		if (click_state == ClickState::MOVE_COLONIST) {
			click_state = ClickState::NONE;
		}
		else {
			click_state = ClickState::MOVE_COLONIST;
		}
		break;
	}
}

void ofApp::ParseBoardClick(int x, int y, int button) {
	ofPoint tile_pos = camera.GetTilePositionAt(x, y);

	switch (click_state) {
	case ClickState::CREATE_WALL:
		board.CreateWall(Wall::Type::COBBLESTONE, tile_pos);
		break;

	case ClickState::DELETE_WALL:
		board.RemoveWall(tile_pos);
		break;

	case ClickState::MOVE_COLONIST:
		break;
	}
}
