#include "wall.h"

Wall::Wall() {
	type_ = Type::STONE_BRICK;
	image_ = &stone_brick_wall_1;
}

Wall::Wall(const Type type) {
	type_ = type;

	int rand = ofRandom(0, 100);
	//Assign Wall texture
	switch (type) {

	case Type::WOOD_PLANKS:
		image_ = &wood_planks_wall_1;
		break;

	case Type::STONE_BRICK:
		image_ = &stone_brick_wall_1;
		break;
	}
}

Wall::Type Wall::GetType() const {
	return type_;
}

const ofImage* Wall::GetImage() const {
	return image_;
}

void Wall::LoadTextures() {
	//Load image files
	wood_planks_wall_1.load("../../resources/wood_planks_wall_1.png");
	stone_brick_wall_1.load("../../resources/stone_brick_wall_1.png");
}

//Define static variables
ofImage wood_planks_wall_1;
ofImage stone_brick_wall_1;