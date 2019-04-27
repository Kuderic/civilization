#include "ofMain.h"
#include "tile.h"

#include <vector>

#pragma once
class Board
{
public:
	//Board dimensions when setup
	static const int kBoardWidth = 20;
	static const int kBoardHeight = 15;

	Board(); // Do we need this? can we combine with setup? should prob have setup do complicated stuff

	const std::array<std::array<Tile, kBoardHeight>, kBoardWidth>& GetTiles() const;
	const Tile& GetTileAt(int x, int y) const;

	void setup();
	void update();
	void draw();

private:
	std::array<std::array<Tile, kBoardHeight>, kBoardWidth> tiles_; //2-D vector of all Tiles
	ofImage grass_tile_1_;
};

