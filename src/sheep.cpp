#include "sheep.h"
#include "board.h"
#include "task.h"

Sheep::Sheep() {
	//Entity default constructor called automatically
	image_ = &sheep_1;
}

Sheep::Sheep(const ofPoint spawn_position) : Entity(spawn_position) {
	//Call superclass constructor passing in position
	image_ = &sheep_1;
}

void Sheep::LoadTextures() {
	//Load image files
	sheep_1.load("../../resources/sheep.png");
}

void Sheep::UpdateTurnAction(const Board& board) {
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

Entity::Activity Sheep::GetNewActivity(const Board& board) {
	return Activity::IDLE;
}

TurnAction Sheep::CreateTurnAction(const Board& board) {
	switch (activity_) {

		//Move in random direction
	case Activity::IDLE:
		std::cout << "MOVE (random)" << std::endl;
		return CreateRandomMove();
	}
}

TurnAction Sheep::CreateRandomMove() {
	int x_rand = (int)ofRandom(-2, 2);
	int y_rand = (int)ofRandom(-2, 2);

	ofPoint current = GetPosition();
	ofPoint dest = ofPoint(current.x + x_rand, current.y + y_rand);

	return TurnAction(Action::MOVE, dest);
}

//Define static variables
ofImage Sheep::sheep_1;