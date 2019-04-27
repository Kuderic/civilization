#include "tile.h"

//needed for array<tile> to work
Tile::Tile() {
	position_ = ofPoint(0, 0, 0);
	width_ = 0;
	height_ = 0;
	floor_ = Floor();
}

Tile::Tile(ofPoint point, int width, int height) {
	this->position_ = point;
	this->width_ = width;
	this->height_ = height;
	floor_ = Floor();
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

void Tile::draw() {
	floor_.GetImage()->draw(position_.x, position_.y, width_, height_);
}
