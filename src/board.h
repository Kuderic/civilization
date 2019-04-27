#include "ofMain.h"
#include "tile.h"
#include "colonist.h"

#include <vector>

#pragma once
class Board
{
public:
	//Board dimensions when setup
	static const int kBoardWidth = 20;
	static const int kBoardHeight = 15;

	Board(); // Do we need this? don't we just call setup?

	const std::array<std::array<Tile, kBoardHeight>, kBoardWidth>& GetTiles() const;
	const Tile& GetTileAt(int x, int y) const;

	void setup();
	void update();
	void draw();

	void DeleteWallTest(int pixel_x, int pixel_y);

private:
	//Generate a 5x5 stone block in setup(). Replace with generative function
	static const int kStoneGenWidth = 5;

	std::array<std::array<Tile, kBoardHeight>, kBoardWidth> tiles_; //2-D vector of all Tiles

	void GenerateTiles();
	//Can make the below into a function which takes Floor::Type and a generative function
	void CreateGrass();
	void CreateStone();
};

