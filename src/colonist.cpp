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
	
	//Make activity based on first available task
	for (Task task : tasks) {
		switch (task.GetType()) {

		case Task::Type::DIG:
			//If not next to the wall, try to create a path to a neighboring tile
			ofPoint wall_position = tasks[0].GetPosition();
			float dist = GetPosition().distance(wall_position);

			if (dist >= 2) {
				std::vector<ofPoint> neighbors = board.GetNeighborsAt(wall_position);

				//Try all neighboring tiles until a valid path is found
				for (ofPoint neighbor : neighbors) {
					current_path_ = board.GetPath(GetPosition(), neighbor);
					if (current_path_.size() > 0) {
						break;
					}
				}
				if (current_path_.size() == 0) {
					//No path was found to dig wall
					break;
				}

				std::cout << "WALK TO DIG" << std::endl;
				return Activity::WALKING;
			} else {
				std::cout << "DIGGING" << std::endl;
				action_tile_ = task.GetPosition();
				return Activity::DIGGING;
			}
		}
	}

	//No possible task was found => IDLE
	std::cout << "IDLE (tasks inaccessible)" << std::endl;
	return Activity::IDLE;
}

TurnAction Colonist::CreateTurnAction(const Board& board) {
	std::cout << "Creating new TurnAction: ";
	switch (activity_) {
	
	//Move in random direction
	case Activity::IDLE:
		std::cout << "Random move" << std::endl;
		return CreateRandomMove();

	//Move along current_path_
	case Activity::WALKING:
		std::cout << "MOVE along path" << std::endl;
		return CreateNextMove();

	//Digging wall at action_tile_
	case Activity::DIGGING:
		std::cout << "DIGGING" << std::endl;
		return TurnAction(Action::DIG, action_tile_);
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


TurnAction Colonist::CreateNextMove() {
	current_path_.pop_back();
	ofPoint dest = current_path_.back();

	return TurnAction(Action::MOVE, dest);
}

//Define static variables
ofImage Colonist::dog_1;