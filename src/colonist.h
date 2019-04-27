#include "ofMain.h"
#pragma once
class Colonist
{
public:
	Colonist();

	const ofImage* GetImage() const;
	static void LoadTextures();

private:
	ofImage* image_;

	static ofImage dog_1;
};