#include "ofMain.h"

#pragma once
class Tile
{
public:

	Tile();
	Tile(ofPoint point, int width, int height, ofImage* image);

	~Tile(); //is this necesasry lol

	int GetWidth();
	int GetHeight();

	void setup();
	void update();
	void draw();

private:
	//ofPoint is another name for the 3d vector class from the openFrameworks math library
	ofPoint position_;

	int width_;
	int height_;
	ofImage* image_;
};

