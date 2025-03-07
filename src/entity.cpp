#include "entity.h"
#include "task.h"

Entity::Entity() {
	position_ = ofPoint(0, 0, 0);
	image_ = nullptr;
	turn_action_ = TurnAction();
	activity_ = Activity::IDLE;
	action_tile_ = ofPoint(0, 0);
}

Entity::Entity(const ofPoint position) {
	position_ = position;
	image_ = nullptr;
	turn_action_ = TurnAction();
	activity_ = Activity::IDLE;
	action_tile_ = ofPoint(0, 0);
}

const ofPoint Entity::GetPosition() const {
	return position_;
}

const ofImage* Entity::GetImage() const {
	return image_;
}

TurnAction& Entity::GetTurnAction() {
	return turn_action_;
}

void Entity::SetPosition(const ofPoint position) {
	position_ = position;
}

void Entity::RemoveTask(const Task* task) {
	auto it = task_map_.find(task);
	if (it != task_map_.end()) {
		task_map_.erase(task_map_.find(task));
	}
}

void Entity::draw(int x, int y, int width, int height) {
	image_->draw(x, y, width, height);
}

//Definition
unordered_map<const Task*, const Entity*> Entity::task_map_;