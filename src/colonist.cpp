#include "colonist.h"

Colonist::Colonist() {
}

const ofImage* Colonist::GetImage() const {
	return image_;
}

//Define static variables
ofImage Colonist::dog_1;