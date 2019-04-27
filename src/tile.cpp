#include "tile.h"

//needed for array<tile> to work
Tile::Tile() {
	this->position_ = ofPoint(0, 0, 0);
	this->width_ = 0;
	this->height_ = 0;
}

Tile::Tile(ofPoint point, int width, int height, const ofImage* image) {
	this->position_ = point;
	this->width_ = width;
	this->height_ = height;
	this->image_ = image;
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

void Tile::draw() {
	image_->draw(position_.x, position_.y, width_, height_);
}
