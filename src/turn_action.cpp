#include "ofMain.h"
#include "turn_action.h"
#pragma once

TurnAction::TurnAction() {
	action_ = Action::IDLE;
}

TurnAction::TurnAction(Action action, ofPoint target) {
	action_ = action;
	target_ = target;
}