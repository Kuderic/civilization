#include "floor.h"

Floor::Floor() {
	type_ = Type::GRASS;
}

Floor::Floor(const Type type) {
	type_ = type;

	int rand = ofRandom(0, 100);
	//Assign floor texture
	switch (type) {
	case Type::GRASS:
		if (rand < 60) {
			image_ = &grass_floor_1_;
		} else if (rand < 90) {
			image_ = &grass_floor_2_;
		} else if (rand < 100) {
			image_ = &grass_floor_3_;
		}
		break;

	case Type::STONE:
		image_ = &stone_floor_1_;
		break;
	}
}


Floor::Type Floor::GetType() const {
	return type_;
}

const ofImage* Floor::GetImage() const {
	return image_;
}

void Floor::LoadTextures() {

	//Load image files
	grass_floor_1_.load("../../resources/grass_floor_1.png");
	grass_floor_2_.load("../../resources/grass_floor_2.png");
	grass_floor_3_.load("../../resources/grass_floor_3.png");
	stone_floor_1_.load("../../resources/stone_floor_1.png");
}

//Define static variables
ofImage Floor::grass_floor_1_;
ofImage Floor::grass_floor_2_;
ofImage Floor::grass_floor_3_;
ofImage Floor::stone_floor_1_;