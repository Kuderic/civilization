#include "tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::draw() {
	ofSetColor(0x00ff00);
	ofDrawRectangle(this->position, this->width, this->height);
}
