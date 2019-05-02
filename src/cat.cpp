#include "cat.h"
#include "board.h"
#include "task.h"

Cat::Cat() {
	//Entity default constructor called automatically
	image_ = &cat_1;
}

Cat::Cat(const ofPoint spawn_position) : Entity(spawn_position) {
	//Call superclass constructor passing in position
	image_ = &cat_1;
}

void Cat::LoadTextures() {
	//Load image files
	cat_1.load("../../resources/cat.png");
}

void Cat::UpdateTurnAction(const Board& board) {
	//Finish turn_action first
	if (!turn_action_.IsComplete()) {
		turn_action_.IncrementProgress();
		return;
	}

	//Update activity_ based on current board
	activity_ = GetNewActivity(board);
	//Create a new TurnAction based on current Activity
	turn_action_ = CreateTurnAction(board);
}

Entity::Activity Cat::GetNewActivity(const Board& board) {
	return Activity::IDLE;
}

TurnAction Cat::CreateTurnAction(const Board& board) {
	switch (activity_) {
	
	//Move in random direction
	case Activity::IDLE:
		std::cout << "MOVE (random)" << std::endl;
		return CreateRandomMove();
	}
}

TurnAction Cat::CreateRandomMove() {
	int x_rand = (int) ofRandom(-2, 2);
	int y_rand = (int) ofRandom(-2, 2);

	ofPoint current = GetPosition();
	ofPoint dest = ofPoint(current.x + x_rand, current.y + y_rand);

	return TurnAction(Action::MOVE, dest);
}

//Define static variables
ofImage Cat::cat_1;