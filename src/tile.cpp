#include "tile.h"

Tile::Tile()
{
}

Tile::Tile(ofPoint point, int width, int height, ofImage* image) {
	this->position = point;
	this->width = width;
	this->height = height;
	this->image = image;
}

Tile::~Tile()
{
}

int Tile::GetWidth() {
	return width;
}

int Tile::GetHeight() {
	return height;
}

void Tile::draw() {
	image->draw(position.x, position.y, width, height);
}
