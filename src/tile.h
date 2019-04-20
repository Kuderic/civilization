#include "ofMain.h"

#pragma once
class Tile
{
public:
	Tile();
	Tile(ofPoint point, int width, int height);

	~Tile();

	//ofPoint is another name for a 3d vector in the openFrameworks math library
	ofPoint position;

	void setup();
	void update();
	void draw();

private:
	int width;
	int height;

	ofImage* image;
};

