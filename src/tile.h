#include "ofMain.h"
#include "floor.h"
#include "wall.h"

#pragma once
class Tile
{
public:
	Tile();
	Tile(ofPoint point, int width, int height);

	int GetWidth() const;
	int GetHeight() const;
	const ofPoint& GetPosition() const;

	void SetFloor(const Floor& floor);
	void SetWall(const Wall& wall);

	void setup();
	void update();
	void draw();

private:
	//ofPoint is another name for the 3d vector class from the openFrameworks math library
	ofPoint position_;

	int width_;
	int height_;
	
	Floor floor_;
	Wall wall_;
};