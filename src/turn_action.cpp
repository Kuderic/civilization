#include "turn_action.h"

TurnAction::TurnAction() {
	action_ = Action::NONE;
	progress_ = 0;
	max_progress_ = kIdleTime;
}

TurnAction::TurnAction(const Action action, const ofPoint target) {
	action_ = action;
	target_ = target;
	progress_ = 0;

	switch (action) {
		case Action::NONE:
			max_progress_ = kIdleTime;
			break;

		case Action::MOVE:
			max_progress_ = kMoveTime;
			break;

		case Action::DIG:
			max_progress_ = kDigTime;
			break;

		case Action::BUILD:
			max_progress_ = kBuildTime;
			break;
	}
}

Action TurnAction::GetAction() const {
	return action_;
}

ofPoint TurnAction::GetTarget() const {
	return target_;
}

int TurnAction::GetProgress() const {
	return progress_;
}

int TurnAction::GetMaxProgress() const {
	return max_progress_;
}

bool TurnAction::IsComplete() const {
	return progress_ >= max_progress_;
}

void TurnAction::IncrementProgress() {
	progress_ += kDefaultIncrement;

	if (progress_ > max_progress_) {
		progress_ = max_progress_;
	}
}

TurnAction& TurnAction::operator++() {
	this->IncrementProgress();
	return *this;
}