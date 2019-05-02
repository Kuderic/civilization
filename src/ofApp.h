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
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void windowResized(int w, int h);
		
private:
	enum class GameState {
		PAUSED,
		PLAY_GAME
	};
	enum class ClickState {
		NONE,
		CREATE_WALL,
		DELETE_WALL,
		DIG_TASK,
		BUILD_TASK,
		REMOVE_TASK
	};
	const static int kInterfaceWidth = 300;	//Pixel width of interface
	const static int kFrameRate = 60;

	GameState game_state;
	ClickState click_state;
	Board board;
	Camera camera;

	//Organize this into an interface class maybe
	ofTrueTypeFont pause_text;
	ofTrueTypeFont interface_text;
	ofTrueTypeFont fps_counter;
	//Music composed by Jamal Green. OST from Equilinox
	ofSoundPlayer background_music;

	void UpdateClickState(int key);
	void ParseBoardClick(int x, int y, int button);
};
