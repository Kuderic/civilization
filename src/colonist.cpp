#include "colonist.h"

Colonist::Colonist() {
}

const ofImage* Colonist::GetImage() const {
	return image_;
}

void Colonist::LoadTextures() {
	//Load image files
	dog_1.load("../../resources/dog_1.png");
}

//Define static variables
ofImage Colonist::dog_1;