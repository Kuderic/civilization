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

void Task::draw(int x, int y, int width, int height) const {
	switch (type_) {
	case Type::DIG:
		dig.draw(x, y, width, height);
	}
}

void Task::LoadTextures() {
	dig.load("../../resources/dig.png");
}

ofImage Task::dig;