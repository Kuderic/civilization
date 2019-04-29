#include "ofMain.h"

#pragma once
class Board;

class Camera
{
public:
	//How many tiles you want to show on screen at once.  16:9 ratio best for fullscreen
	const static int kDefaultWidth = 16 * 2;
	const static int kDefaultHeight = 9 * 2;

	Camera();

	ofPoint GetPosition() const;
	ofPoint GetTilePosition(int pixel_x, int pixel_y) const;

	void SetBoard(const Board* board);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetPosition(const ofPoint position);

	void KeyPressed(int key);
	void KeyReleased(int key);

	void draw();
	void update(); // updates position based on key pressed booleans

private:
	int width_;
	int height_;
	ofPoint position_;
	const Board* board_;

	/*	Booleans to track which keys are pressed
		This is necessary because keyPressed() only returns the most recent key press
		So booleans are needed to track sumultaneous key pressed */
	bool up_pressed_;
	bool right_pressed_;
	bool down_pressed_;
	bool left_pressed_;
};

