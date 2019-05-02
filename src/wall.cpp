#include "wall.h"

Wall::Wall() {
	type_ = Type::STONE_BRICK;
	image_ = &stone_brick_wall_1;
}

Wall::Wall(const Type type) {
	type_ = type;

	//Assign Wall texture
	switch (type) {
	case Type::EMPTY:
		image_ = nullptr;
		break;

	case Type::WOOD_PLANKS:
		image_ = &wood_planks_wall_1;
		break;

	case Type::STONE_BRICK:
		image_ = &stone_brick_wall_1;
		break;

	case Type::COBBLESTONE:
		image_ = &cobblestone_wall_1;
		break;
	}
}

Wall::Type Wall::GetType() const {
	return type_;
}

const ofImage* Wall::GetImage() const {
	return image_;
}

void Wall::DropItem() const {
	//This will drop an item one day
}


void Wall::PlayBreakSound() const {
	int rand = ofRandom(0, 100);
	switch (type_) {
	case Type::COBBLESTONE:
		if (rand < 25) {
			stone_1.play();
		}
		else if (rand < 50) {
			stone_2.play();
		}
		else if (rand < 75) {
			stone_3.play();
		}
		else if (rand < 100) {
			stone_4.play();
		}
		break;

	default:
		stone_1.play();
		break;
	}
}

void Wall::LoadTextures() {
	//Load image files
	wood_planks_wall_1.load("../../resources/wood_planks_wall_1.png");
	stone_brick_wall_1.load("../../resources/stone_brick_wall_1.png");
	cobblestone_wall_1.load("../../resources/cobblestone_wall_1.png");

	//Load sounds
	stone_1.load("../../resources/stone1.ogg");
	stone_2.load("../../resources/stone2.ogg");
	stone_3.load("../../resources/stone3.ogg");
	stone_4.load("../../resources/stone4.ogg");
}

//Define static variables
ofImage Wall::wood_planks_wall_1;
ofImage Wall::stone_brick_wall_1;
ofImage Wall::cobblestone_wall_1;
ofSoundPlayer Wall::stone_1;
ofSoundPlayer Wall::stone_2;
ofSoundPlayer Wall::stone_3;
ofSoundPlayer Wall::stone_4;