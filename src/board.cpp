#include "board.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::setup() {
	for (int i = 0; i < 5; i++) {
		ofPoint point = ofPoint(10 * i, 0, 0);
		Tile new_tile = Tile(point, 10, 10);

		tiles.push_back(new_tile);
	}
}

void Board::draw() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].draw();
	}
}