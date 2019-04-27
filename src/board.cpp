#include "board.h"

Board::Board()
{
}

Board::~Board()
{
}

const std::array<std::array<Tile, Board::kBoardHeight>, Board::kBoardWidth>& Board::GetTiles() const {
	return tiles_;
}
const Tile& Board::GetTileAt(int x, int y) {
	return tiles_[x][y];
}

void Board::setup() {
	//Load image files
	grass_tile_1_.load("../../resources/grass_tile_3.png");
	
	int win_width = ofGetWindowWidth();
	int win_height = ofGetWindowHeight();

	for (int i = 0; i < kBoardWidth; i++) {
		for (int j = 0; j < kBoardHeight; j++) {

			int tile_width = win_width / kBoardWidth;
			int tile_height = win_height / kBoardHeight;

			int x = tile_width * i;
			int y = tile_height * j;
			
			ofPoint point = ofPoint(x, y, 0);
			Tile new_tile = Tile(point, tile_width, tile_height, &grass_tile_1_);

			tiles_[i][j] = new_tile;
		}
	}
}

void Board::draw() {
	for (int i = 0; i < tiles_.size(); i++) {
		for (int j = 0; j < tiles_[0].size(); j++) {
			tiles_[i][j].draw();
		}
	}
}