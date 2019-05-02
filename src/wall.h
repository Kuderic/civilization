#include "ofMain.h"
#pragma once
class Wall
{
public:
	enum class Type {
		EMPTY,
		WOOD_PLANKS,
		COBBLESTONE,
		STONE_BRICK
	};

	Wall();
	Wall(const Type type);

	Type GetType() const;
	const ofImage* GetImage() const;

	void DropItem() const;
	void PlayBreakSound() const;

	static void LoadTextures();
	static void LoadSounds();

private:
	ofImage* image_;
	Type type_;

	static ofImage wood_planks_wall_1;
	static ofImage stone_brick_wall_1;
	static ofImage cobblestone_wall_1;
	static ofSoundPlayer stone_1;
	static ofSoundPlayer stone_2;
	static ofSoundPlayer stone_3;
	static ofSoundPlayer stone_4;
};