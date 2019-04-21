#include "board.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::setup(int numXTiles, int numYTiles) {
	//Load image files
	grass_tile_1.load("../../resources/grass_tile_1.png");
	
	int win_width = ofGetWindowWidth();
	int win_height = ofGetWindowHeight();

	for (int i = 0; i < numXTiles; i++) {
		for (int j = 0; j < numXTiles; j++) {

			int tile_width = win_width / numXTiles;
			int tile_height = win_height / numYTiles;

			int x = tile_width * i;
			int y = tile_height * j;

			ofPoint point = ofPoint(x, y, 0);
			Tile new_tile = Tile(point, tile_width, tile_height, &grass_tile_1);

			tiles.push_back(new_tile);
		}
	}
}

void Board::draw() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].draw();
	}
}