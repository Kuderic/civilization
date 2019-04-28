#include "colonist.h"

Colonist::Colonist() {
	//Entity default constructor called automatically
	image_ = &dog_1;
}

Colonist::Colonist(const ofPoint spawn_position) : Entity(spawn_position) {
	//Call superclass constructor passing in position
	image_ = &dog_1;
}

void Colonist::LoadTextures() {
	//Load image files
	dog_1.load("../../resources/dog_1.png");
}

void Colonist::UpdateTurnAction(const Board& board) {
	if (turn_action_.GetAction() != Action::MOVE) {
		ofPoint my_pos = GetPosition();
		ofPoint target_pos = ofPoint(my_pos.x + 1, my_pos.y + 1, my_pos.z);

		turn_action_ = TurnAction(Action::MOVE, target_pos, this);
	}
	if (turn_action_.IsComplete()) {
		ofPoint my_pos = GetPosition();
		ofPoint target_pos = ofPoint(my_pos.x + 1, my_pos.y + 1, my_pos.z);

		turn_action_ = TurnAction(Action::MOVE, target_pos, this);
	}

	turn_action_.IncrementProgress();
}

//Define static variables
ofImage Colonist::dog_1;