#include "entity.h"

Entity::Entity() {
	position_ = ofPoint(0, 0, 0);
	image_ = nullptr;
}

Entity::Entity(const ofPoint position) {
	position_ = position;
	image_ = nullptr;
}

const ofImage* Entity::GetImage() const {
	return image_;
}

const ofPoint Entity::GetPosition() const {
	return position_;
}

void Entity::SetPosition(int x, int y) {
	position_.x = x;
	position_.y = y;
}

void Entity::draw(int x, int y, int width, int height) {
	image_->draw(x, y, width, height);
}