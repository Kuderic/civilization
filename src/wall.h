#include "ofMain.h"
#pragma once
class Wall
{
public:
	enum class Type {
		WOOD_PLANKS,
		STONE_BRICK
	};

	Wall();
	Wall(const Type type);

	Type GetType() const;
	const ofImage* GetImage() const;

	static void LoadTextures();

private:
	ofImage* image_;
	Type type_;

	static ofImage wood_planks_wall_1;
	static ofImage stone_brick_wall_1;
};