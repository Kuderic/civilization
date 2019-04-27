#include "floor.h"

Floor::Floor() {
}

Floor::Type Floor::GetType() const {
	return type_;
}

const ofImage* Floor::GetImage() const {
	return image_;
}

void Floor::LoadTextures() {
	//Load image files
	grass_floor_1_.load("../../resources/grass_tile_1.png");
	grass_floor_2_.load("../../resources/grass_tile_2.png");
	grass_floor_3_.load("../../resources/grass_tile_3.png");
	stone_floor_1_.load("../../resources/stone_tile_1.png");
}