#include "colonist.h"

Colonist::Colonist() {
	//Entity default constructor called automatically
	image_ = &dog_1;
}

Colonist::Colonist(const ofPoint position) : Entity(position) {
	//Call superclass constructor passing in position
	image_ = &dog_1;
}

void Colonist::LoadTextures() {
	//Load image files
	dog_1.load("../../resources/dog_1.png");
}

//Define static variables
ofImage Colonist::dog_1;

void Colonist::update() {
	position_.x = position_.x + 1;
	position_.y = position_.y + 1;
}