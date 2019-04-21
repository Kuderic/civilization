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

	void setup(int numXTiles, int numYTiles);
	void update();
	void draw();

private:
	ofImage grass_tile_1;
};

