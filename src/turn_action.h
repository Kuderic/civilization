#include "ofMain.h"
#pragma once

enum class Action {
	IDLE,
	MOVE
};

class TurnAction {
public:
	Action action_;
	ofPoint target_;

	TurnAction();
	TurnAction(Action action, ofPoint target);
};