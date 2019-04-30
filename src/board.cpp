#include "board.h"

Board::Board() {
}

const std::array<std::array<Tile, Board::kBoardHeight>, Board::kBoardWidth>& Board::GetTiles() const {
	return tiles_;
}

const std::vector<Entity*>& Board::GetEntities() const {
	return entities_;
}

const Tile* Board::GetTileAt(ofPoint position) const {
	int x = position.x;
	int y = position.y;

	if (x < 0 || x >= kBoardWidth || y < 0 || y >= kBoardHeight) {
		return nullptr;
	}

	return &tiles_[x][y];
}

//Check the 8 surrounding tiles. If all neighboring tiles have walls, return true
bool Board::IsSurroundedByWallsAt(ofPoint position) const {
	int x = position.x;
	int y = position.y;

	for (int i = x - 1; i < x + 2; i++) {
		for (int j = y - 1; j < y + 2; j++) {
			//Skip over self
			if (i == x && j == y) {
				continue;
			}
			const Tile* neighbor = GetTileAt(ofPoint(i, j));

			//Check that neighbor exists (for edge tiles)
			if (!neighbor) {
				continue;
			} else if (!neighbor->HasWall()) {
				return false;
			}
		}
	}
	return true;
}

//Generate gameboard
void Board::setup() {
	GenerateTiles();
	CreateGrass();
	CreateStone();

	CreateColonists();
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

//Called by camera when a tile is clicked
void Board::TileClicked(const ofPoint position) {
	int x = position.x;
	int y = position.y;
	//Check that x, y is part of the board
	if (x < kBoardWidth && y < kBoardHeight) {
		tiles_[x][y].SetWall(Wall(Wall::Type::EMPTY));
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