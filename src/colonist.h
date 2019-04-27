#include "ofMain.h"
#include "entity.h"
#pragma once
class Colonist : public Entity
{
public:
	Colonist();
	Colonist(const ofPoint position);

	static void LoadTextures();

	void update();

private:
	static ofImage dog_1;
};