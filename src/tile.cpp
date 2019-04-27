#include "tile.h"

Tile::Tile() {
	position_ = ofPoint(0, 0, 0);
	width_ = 0;
	height_ = 0;
	floor_ = Floor();
	wall_ = Wall(Wall::Type::EMPTY);
}

Tile::Tile(ofPoint point, int width, int height) {
	this->position_ = point;
	this->width_ = width;
	this->height_ = height;
	floor_ = Floor();
	wall_ = Wall(Wall::Type::EMPTY);
}

const ofPoint& Tile::GetPosition() const {
	return position_;
}

int Tile::GetWidth() const {
	return width_;
}

int Tile::GetHeight() const {
	return height_;
}

void Tile::SetFloor(const Floor& floor) {
	floor_ = floor;
}

void Tile::SetWall(const Wall& wall) {
	wall_ = wall;
}

void Tile::draw() {
	//If wall exists, draw that instead of floor
	if (wall_.GetImage()) {
		wall_.GetImage()->draw(position_.x, position_.y, width_, height_);
	} else {
		floor_.GetImage()->draw(position_.x, position_.y, width_, height_);
	}
}
