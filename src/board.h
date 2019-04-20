#include "ofMain.h"
#include "tile.h"

#include <vector>

#pragma once
class Board
{
public:

	Board();
	~Board();

	std::vector<Tile> tiles;

	void setup();
	void update();
	void draw();
};

