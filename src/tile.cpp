#include "tile.h"

Tile::Tile()
{
}

Tile::Tile(ofPoint point, int width, int height, ofImage* image) {
	this->position_ = point;
	this->width_ = width;
	this->height_ = height;
	this->image_ = image;
}

Tile::~Tile()
{
}

int Tile::GetWidth() {
	return width_;
}

int Tile::GetHeight() {
	return height_;
}

void Tile::draw() {
	image_->draw(position_.x, position_.y, width_, height_);
}
