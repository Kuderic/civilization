#include "ofMain.h"
#pragma once

class Entity;
enum class Action {
	IDLE,
	MOVE,
	DIG,
	BUILD
};

class TurnAction {
public:
	TurnAction();
	TurnAction(const Action action, const ofPoint target, const Entity* owner);

	const Entity* GetOwner() const;
	Action GetAction() const;
	ofPoint GetTarget() const;
	int GetProgress() const;
	int GetMaxProgress() const;
	bool IsComplete() const;

	//Increment amount will vary based on owner properties (skill, speed, health)
	//This way, different entities can have different speeds for actions
	void IncrementProgress();
	TurnAction& operator++();

private:
	const Entity* owner_;

	Action action_;
	ofPoint target_;
	int progress_; //Increments each frame
	int max_progress_; //Required to do action

	const static int kDefaultIncrement = 20;
	//Max time for various actions
	const static int kIdleTime = 50;
	const static int kMoveTime = 300;
	const static int kDigTime = 1500;
};