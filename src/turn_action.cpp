#include "turn_action.h"

TurnAction::TurnAction() {
	action_ = Action::IDLE;
	progress_ = 0;
	max_progress_ = kIdleTime;
	owner_ = nullptr;
}

TurnAction::TurnAction(const Action action, const ofPoint target, const Entity* owner) {
	action_ = action;
	target_ = target;
	progress_ = 0;
	owner_ = owner;

	switch (action) {
		case Action::IDLE:
			max_progress_ = kIdleTime;
			break;

		case Action::MOVE:
			max_progress_ = kMoveTime;
			break;

		case Action::DIG:
			max_progress_ = kDigTime;
			break;
	}
}

const Entity* TurnAction::GetOwner() const {
	return owner_;
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