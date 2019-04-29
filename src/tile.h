#include "ofMain.h"
#include "floor.h"
#include "wall.h"

#pragma once
class Tile
{
public:
	Tile();

	const Floor& GetFloor() const;
	const Wall& GetWall() const;

	void SetFloor(const Floor& floor);
	void SetWall(const Wall& wall);

	void draw(int x, int y, int width, int height) const;

private:	
	Floor floor_;
	Wall wall_;
};