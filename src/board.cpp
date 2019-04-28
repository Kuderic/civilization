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

	CreateColonists();
}

void Board::draw() {
	//Calculate the width and height each tile should be drawn with
	int tile_width = ofGetWindowWidth() / kBoardWidth;
	int tile_height = ofGetWindowHeight() / kBoardHeight;

	//Draw tiles
	for (int x = 0; x < tiles_.size(); x++) {
		for (int y = 0; y < tiles_[0].size(); y++) {
			//Calculate the pixel position of each tile
			int pixel_x = tile_width * x;
			int pixel_y = tile_height * y;

			tiles_[x][y].draw(pixel_x, pixel_y, tile_width, tile_height);
		}
	}

	//Draw entities after tiles
	for (int i = 0; i < entities_.size(); i++) {
		int pixel_x = tile_width * entities_[i]->GetPosition().x;
		int pixel_y = tile_height * entities_[i]->GetPosition().y;

		entities_[i]->draw(pixel_x, pixel_y, tile_width, tile_height);
	}
}

void Board::update() {
	for (int i = 0; i < entities_.size(); i++) {
		Entity& entity = *entities_[i];

		//Give entity a reference to board so it can update its action
		entity.UpdateTurnAction(*this);

		TurnAction& action = entity.GetTurnAction();
		/* Parse action for entity if done
			Note: I handle parsing in Board because board is the only class that has access to everything
			E.g. if action is digging a wall, board can remove the wall when action is complete*/
		if (action.IsComplete()) {
			switch (action.GetAction()) {
			case Action::MOVE:
				entity.SetPosition(action.GetTarget());
			}
		}
	}
}

void Board::GenerateTiles() {
	//Generate a kBoardWidth by kBoardHeight sized tile board
	for (int i = 0; i < kBoardWidth; i++) {
		for (int j = 0; j < kBoardHeight; j++) {
			Tile new_tile = Tile();
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
			tiles_[i][j].SetFloor(Floor(Floor::Type::STONE));
			tiles_[i][j].SetWall(Wall(Wall::Type::COBBLESTONE));
		}
	}
}

void Board::CreateColonists() {
	for (int i = 0; i < kNumColonists; i++) {
		Colonist* colonist = new Colonist(ofPoint(i, 0, 0));
		entities_.push_back(colonist);
	}
}

//Click on a tile to delete the wall there
void Board::DeleteWallTest(int pixel_x, int pixel_y) {
	int tile_width = ofGetWindowWidth() / kBoardWidth;
	int tile_height = ofGetWindowHeight() / kBoardHeight;
	int x = pixel_x / tile_width;
	int y = pixel_y / tile_height;

	tiles_[x][y].SetWall(Wall(Wall::Type::EMPTY));
}