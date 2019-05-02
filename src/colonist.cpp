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
	//std::cout << "=====================" << std::endl;
	//std::cout << "I am doggo " << this << std::endl;
	const std::vector<Task>& tasks = board.GetTasks();
	
	if (tasks.size() == 0) {
		//std::cout << "New Activity: IDLE" << std::endl;
		return Activity::IDLE;
	}

	//Make activity based on first available task
	for (int i = 0; i < tasks.size(); i++) {
		const Task& task = tasks[i];
		//std::cout << "Looking at task " << &task << std::endl;

		//If another dog is doing this task, go to the next task
		auto search = task_map_.find(&task);
		if (search != task_map_.end()) {
			if (task_map_[&task] != this) {
				//std::cout << "Another doggo has this task" << std::endl;
				continue;
			}
		}

		ofPoint wall_position;
		float dist;

		switch (task.GetType()) {
		case Task::Type::DIG:
			wall_position = task.GetPosition();

			//If not adjacent to wall, try to create a path to a neighboring tile of wall
			dist = GetPosition().distance(wall_position);
			if (dist >= 2) {
				//Get rid of current path
				std::vector<ofPoint> empty;
				current_path_ = empty;

				std::vector<ofPoint> neighbors = board.GetEmptyNeighborsAt(wall_position);
				//Try all empty neighboring tiles until a valid path is found
				for (ofPoint neighbor : neighbors) {
					current_path_ = board.GetPath(GetPosition(), neighbor);
					if (current_path_.size() > 0) {
						break;
					}
				}
				if (current_path_.size() == 0) {
					//No path was found to dig wall. Go to next task
					break;
				}
				//std::cout << "New Activity: WALKING TO DIG LOCATION" << std::endl;
				task_map_[&task] = this;
				return Activity::WALKING;

			} else {
				//std::cout << "New Activity: DIGGING" << std::endl;
				action_tile_ = task.GetPosition();
				task_map_[&task] = this;
				return Activity::DIGGING;
			}
			break;

		case Task::Type::BUILD:
			wall_position = task.GetPosition();

			//If not adjacent to build spot, try to create a path to a neighboring tile of wall
			dist = GetPosition().distance(wall_position);
			if (dist >= 2) {
				//Get rid of current path
				std::vector<ofPoint> empty;
				current_path_ = empty;

				std::vector<ofPoint> neighbors = board.GetEmptyNeighborsAt(wall_position);
				for (ofPoint neighbor : neighbors) {
					current_path_ = board.GetPath(GetPosition(), neighbor);
					if (current_path_.size() > 0) {
						break;
					}
				}
				if (current_path_.size() == 0) {
					break;
				}
				//std::cout << "New Activity: WALKING TO DIG LOCATION" << std::endl;
				task_map_[&task] = this;
				return Activity::WALKING;

			}
			else {
				//std::cout << "New Activity: DIGGING" << std::endl;
				action_tile_ = task.GetPosition();
				task_map_[&task] = this;
				return Activity::BUILDING;
			}
			break;
		}
	}

	//No possible task was found => IDLE
	//std::cout << "New Activity: IDLE (tasks inaccessible)" << std::endl;
	return Activity::IDLE;
}

TurnAction Colonist::CreateTurnAction(const Board& board) {
	//std::cout << "Creating new TurnAction: ";
	switch (activity_) {
	
	//Move in random direction
	case Activity::IDLE:
		//std::cout << "MOVE (random)" << std::endl;
		return CreateRandomMove();

	//Move along current_path_
	case Activity::WALKING:
		//std::cout << "MOVE (along current_path_)" << std::endl;
		return CreateNextMove();

	//Digging wall at action_tile_
	case Activity::DIGGING:
		//std::cout << "DIGGING" << std::endl;
		return TurnAction(Action::DIG, action_tile_);

	//Building wall at action_tile_
	case Activity::BUILDING:
		//std::cout << "DIGGING" << std::endl;
		return TurnAction(Action::BUILD, action_tile_);
	}
}

TurnAction Colonist::CreateRandomMove() {
	int x_rand = (int) ofRandom(-2, 2);
	int y_rand = (int) ofRandom(-2, 2);

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