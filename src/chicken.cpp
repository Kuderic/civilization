#include "chicken.h"
#include "board.h"
#include "task.h"

Chicken::Chicken() {
	//Entity default constructor called automatically
	image_ = &chicken_1;
}

Chicken::Chicken(const ofPoint spawn_position) : Entity(spawn_position) {
	//Call superclass constructor passing in position
	image_ = &chicken_1;
}

void Chicken::LoadTextures() {
	//Load image files
	chicken_1.load("../../resources/chicken.png");
}

void Chicken::UpdateTurnAction(const Board& board) {
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

Entity::Activity Chicken::GetNewActivity(const Board& board) {
	return Activity::IDLE;
}

TurnAction Chicken::CreateTurnAction(const Board& board) {
	switch (activity_) {

		//Move in random direction
	case Activity::IDLE:
		std::cout << "MOVE (random)" << std::endl;
		return CreateRandomMove();
	}
}

TurnAction Chicken::CreateRandomMove() {
	int x_rand = (int)ofRandom(-2, 2);
	int y_rand = (int)ofRandom(-2, 2);

	ofPoint current = GetPosition();
	ofPoint dest = ofPoint(current.x + x_rand, current.y + y_rand);

	return TurnAction(Action::MOVE, dest);
}

//Define static variables
ofImage Chicken::chicken_1;