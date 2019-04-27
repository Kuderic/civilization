#include "board.h"

Board::Board() {
}

const std::array<std::array<Tile, Board::kBoardHeight>, Board::kBoardWidth>& Board::GetTiles() const {
	return tiles_;
}

const Tile& Board::GetTileAt(int x, int y) const {
	return tiles_[x][y];
}

//Generate gameboard
void Board::setup() {
	GenerateTiles();
	CreateGrass();
	CreateStone();
}

void Board::draw() {
	for (int i = 0; i < tiles_.size(); i++) {
		for (int j = 0; j < tiles_[0].size(); j++) {
			tiles_[i][j].draw();
		}
	}
}

void Board::GenerateTiles() {
	//Generate a kBoardWidth by kBoardHeight sized tile board
	int tile_width = ofGetWindowWidth() / kBoardWidth;
	int tile_height = ofGetWindowHeight() / kBoardHeight;

	for (int i = 0; i < kBoardWidth; i++) {
		for (int j = 0; j < kBoardHeight; j++) {
			int x = tile_width * i;
			int y = tile_height * j;

			ofPoint point = ofPoint(x, y, 0);
			Tile new_tile = Tile(point, tile_width, tile_height);

			tiles_[i][j] = new_tile;
		}
	}
}

void Board::CreateGrass() {
	//Generate grass on every board tile
	for (int i = 0; i < kBoardWidth; i++) {
		for (int j = 0; j < kBoardHeight; j++) {
			tiles_[i][j].SetFloor(Floor(Floor::Type::GRASS));
		}
	}
}

void Board::CreateStone() {
	//Generate stone in the bottom right corner (for now)
	for (int i = kBoardWidth - kStoneGenWidth; i < kBoardWidth; i++) {
		for (int j = kBoardHeight - kStoneGenWidth; j < kBoardHeight; j++) {
			std::cout << "stone";
			tiles_[i][j].SetFloor(Floor(Floor::Type::STONE));
		}
	}
}