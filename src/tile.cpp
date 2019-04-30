#include "tile.h"

Tile::Tile() {
	floor_ = Floor();
	wall_ = Wall(Wall::Type::EMPTY);
}

const Floor& Tile::GetFloor() const {
	return floor_;
}

const Wall& Tile::GetWall() const {
	return wall_;
}

void Tile::SetFloor(const Floor& floor) {
	floor_ = floor;
}

void Tile::SetWall(const Wall& wall) {
	wall_ = wall;
}

bool Tile::HasWall() const {
	return wall_.GetType() != Wall::Type::EMPTY;
}

void Tile::draw(int x, int y, int width, int height) const {
	//If wall exists, draw that instead of floor
	if (this->HasWall()) {
		wall_.GetImage()->draw(x, y, width, height);
	} else {
		floor_.GetImage()->draw(x, y, width, height);
	}
}
