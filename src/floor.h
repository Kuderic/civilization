#include "ofMain.h"
#pragma once
class Floor
{
public:
	enum class Type {
		GRASS,
		STONE
	};

	Floor();
	Floor(const Type type);

	Type GetType() const;
	const ofImage* GetImage() const;

	static void LoadTextures();

private:
	ofImage* image_;
	Type type_;

	//Images for floor textures
	//Should I put this in a vector? Should I make it its own class?
	static ofImage grass_floor_1_;
	static ofImage grass_floor_2_;
	static ofImage grass_floor_3_;
	static ofImage stone_floor_1_;
	static ofImage stone_floor_2_;
};