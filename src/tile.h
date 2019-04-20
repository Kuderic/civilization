#include "ofMain.h"

#pragma once
class Tile
{
public:
	Tile();
	~Tile();

	//ofPoint is another name for a 3d vector in the openFrameworks math library
	ofPoint position;
	int width;
	int height;

	void setup();
	void update();
	void draw();

	ofImage* image;
};

