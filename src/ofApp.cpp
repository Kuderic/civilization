#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Dog Fortress");
	ofBackground(ofColor::black);
	ofSetFrameRate(kFrameRate);
	game_state = GameState::PLAY_GAME;
	click_state = ClickState::NONE;

	Floor::LoadTextures();
	Wall::LoadTextures();
	Colonist::LoadTextures();
	Task::LoadTextures();
	pause_text.load("../../resources/SEA_GARDENS.ttf", 50);
	interface_text.load("../../resources/SEA_GARDENS.ttf", 20);
	fps_counter.load("../../resources/SEA_GARDENS.ttf", 15);

	background_music.load("../../resources/background.mp3");
	background_music.setVolume(40);
	background_music.play();

	//Board dimensions can be modified in board.h
	board.setup();
	camera.SetBoard(&board);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (game_state == GameState::PLAY_GAME) {
		board.update();
	}
	camera.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(ofColor::white); //	White color needed to draw images normally
	camera.draw();

	if (game_state == GameState::PAUSED) {
		ofSetColor(ofColor::yellow);
		pause_text.drawString("PAUSED", ofGetWindowWidth() - kInterfaceWidth, ofGetWindowHeight());
	}

	//	Draw interface
	//	I know this has magic numbers but I plan to change this completely
	ofSetColor(ofColor::white);
	interface_text.drawString("'w'|Create Wall", ofGetWindowWidth() - kInterfaceWidth, 30);
	interface_text.drawString("'x'|Delete Wall", ofGetWindowWidth() - kInterfaceWidth, 60);
	interface_text.drawString("'d'|Dig Wall", ofGetWindowWidth() - kInterfaceWidth, 90);
	interface_text.drawString("'r'|Remove Task", ofGetWindowWidth() - kInterfaceWidth, 120);

	//Draw currently selected action in yellow
	ofSetColor(ofColor::yellow);
	switch (click_state) {
	case ClickState::CREATE_WALL:
		interface_text.drawString("'w'|Create Wall", ofGetWindowWidth() - kInterfaceWidth, 30);
		break;

	case ClickState::DELETE_WALL:
		interface_text.drawString("'x'|Delete Wall", ofGetWindowWidth() - kInterfaceWidth, 60);
		break;

	case ClickState::DIG_TASK:
		interface_text.drawString("'d'|Dig Wall", ofGetWindowWidth() - kInterfaceWidth, 90);
		break;

	case ClickState::REMOVE_TASK:
		interface_text.drawString("'r'|Remove Task", ofGetWindowWidth() - kInterfaceWidth, 120);
		break;
	}

	//Update Framerate counter
	std::stringstream stream;
	stream << "FPS: " << ofGetFrameRate();
	ofSetColor(ofColor::white);
	fps_counter.drawString(stream.str(), ofGetWindowWidth() - kInterfaceWidth, ofGetWindowHeight() - 5);
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
void ofApp::mouseDragged(int x, int y, int button) {
	ParseBoardClick(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ParseBoardClick(x, y, button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	//Recalculate camera width and height
	camera.SetPixelWidth(ofGetWindowWidth() - kInterfaceWidth);
	camera.SetPixelHeight(ofGetWindowHeight());
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

	case 'x':
		if (click_state == ClickState::DELETE_WALL) {
			click_state = ClickState::NONE;
		}
		else {
			click_state = ClickState::DELETE_WALL;
		}
		break;

	case 'd':
		if (click_state == ClickState::DIG_TASK) {
			click_state = ClickState::NONE;
		}
		else {
			click_state = ClickState::DIG_TASK;
		}
		break;

	case 'r':
		if (click_state == ClickState::REMOVE_TASK) {
			click_state = ClickState::NONE;
		}
		else {
			click_state = ClickState::REMOVE_TASK;
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

	case ClickState::DIG_TASK:
		board.CreateDigTask(tile_pos);
		break;

	case ClickState::REMOVE_TASK:
		board.RemoveTask(tile_pos);
		break;
	}
}
