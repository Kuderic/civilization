#include "ofMain.h"

#pragma once
class Tile
{
public:

	Tile();
	Tile(ofPoint point, int width, int height, const ofImage* image);

	int GetWidth() const;
	int GetHeight() const;
	const ofPoint& GetPosition() const;

	void setup();
	void update();
	void draw();

private:
	//ofPoint is another name for the 3d vector class from the openFrameworks math library
	ofPoint position_;

	int width_;
	int height_;
	const ofImage* image_;
};