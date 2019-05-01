#include "task.h"

Task::Task(Task::Type type, ofPoint position) {
	type_ = type;
	position_ = position;
}

Task::Type Task::GetType() const {
	return type_;
}

ofPoint Task::GetPosition() const {
	return position_;
}