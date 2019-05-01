#pragma once

#include "ofMain.h"
#include "board.h"
#include "camera.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
private:
	enum class GameState {
		PAUSED,
		PLAY_GAME
	};
	enum class ClickState {
		NONE,
		CREATE_WALL,
		DELETE_WALL,
		MOVE_COLONIST
	};
	const static int kFrameRate = 30;

	GameState game_state;
	ClickState click_state;
	Board board;
	Camera camera;
	//Organize this into an interface class maybe
	ofTrueTypeFont pause_text;
	ofTrueTypeFont interface_text;

	void UpdateClickState(int key);
	void ParseBoardClick(int x, int y, int button);
};
