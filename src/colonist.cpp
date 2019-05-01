#include "colonist.h"
#include "board.h"
#include "task.h"

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
	//Finish turn_action first
	if (!turn_action_.IsComplete()) {
		turn_action_.IncrementProgress();
		return;
	}

	//Update activity_ based on current board tasks
	activity_ = GetNewActivity(board);
	//Create a new TurnAction based on current Activity
	turn_action_ = CreateTurnAction(board);
}

Entity::Activity Colonist::GetNewActivity(const Board& board) {
	std::cout << "Getting new activity: ";
	const std::vector<Task>& tasks = board.GetTasks();
	
	if (tasks.size() == 0) {
		std::cout << "IDLE" << std::endl;
		return Activity::IDLE;
	}
}

TurnAction Colonist::CreateTurnAction(const Board& board) {
	std::cout << "Creating new TurnAction: ";
	switch (activity_) {
	
	//Move in random direction
	case Activity::IDLE:
		std::cout << "Random move" << std::endl;
		return CreateRandomMove();
	}
}

TurnAction Colonist::CreateRandomMove() {
	int x_rand = (int) ofRandom(-2, 2);
	int y_rand = (int) ofRandom(-2, 2);
	std::cout << x_rand << std::endl;
	std::cout << y_rand << std::endl;

	ofPoint current = GetPosition();
	ofPoint dest = ofPoint(current.x + x_rand, current.y + y_rand);

	return TurnAction(Action::MOVE, dest);
}

//Define static variables
ofImage Colonist::dog_1;