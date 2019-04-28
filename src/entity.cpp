#include "entity.h"

Entity::Entity() {
	position_ = ofPoint(0, 0, 0);
	image_ = nullptr;
	turn_action_ = TurnAction();
}

Entity::Entity(const ofPoint position) {
	position_ = position;
	image_ = nullptr;
	turn_action_ = TurnAction();
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

void Entity::draw(int x, int y, int width, int height) {
	image_->draw(x, y, width, height);
}