#include "ofMain.h"

#include <vector>

#pragma once
class Board
{
public:
	class Tile;

	Board();
	~Board();

	std::vector<Tile> tiles;

	void setup();
	void update();
	void draw();
};

