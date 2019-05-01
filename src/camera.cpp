#include "camera.h"
#include "board.h"

Camera::Camera() {
	width_ = kDefaultWidth;
	height_ = kDefaultHeight;
	position_ = ofPoint(0, 0, 0);
	board_ = nullptr;
}

ofPoint Camera::GetPosition() const {
	return position_;
}

//Called when mouse clicks
ofPoint Camera::GetTilePositionAt(int pixel_x, int pixel_y) const {
	int tile_width = ofGetWindowWidth() / width_;
	int tile_height = ofGetWindowHeight() / height_;
	int x = position_.x + pixel_x / tile_width;
	int y = position_.y + pixel_y / tile_height;

	return ofPoint(x, y, 0);
}

void Camera::SetBoard(const Board* board) {
	board_ = board;
}

void Camera::SetHeight(int height) {
	height_ = height;
}

void Camera::SetWidth(int width) {
	width_ = width;
}

void Camera::SetPosition(const ofPoint position) {
	position_ = position;
}

void Camera::KeyPressed(int key) {
	switch (key) {
	case OF_KEY_UP:
		up_pressed_ = true;
		break;
	case OF_KEY_RIGHT:
		right_pressed_ = true;
		break;
	case OF_KEY_DOWN:
		down_pressed_ = true;
		break;
	case OF_KEY_LEFT:
		left_pressed_ = true;
		break;
	}
}

void Camera::KeyReleased(int key) {
	switch (key) {
	case OF_KEY_UP:
		up_pressed_ = false;
		break;
	case OF_KEY_RIGHT:
		right_pressed_ = false;
		break;
	case OF_KEY_DOWN:
		down_pressed_ = false;
		break;
	case OF_KEY_LEFT:
		left_pressed_ = false;
		break;
	}
}

void Camera::draw() {
	const std::vector<Entity*>& entities = board_->GetEntities();

	//Calculate the width and height each tile should be drawn with
	int tile_width = ofGetWindowWidth() / width_;
	int tile_height = ofGetWindowHeight() / height_;

	//Iterate through tiles
	for (int i = 0; i < width_; i++) {
		for (int j = 0; j < height_; j++) {
			ofPoint tile_position = ofPoint(i + position_.x, j + position_.y);
			const Tile* tile = board_->GetTileAt(tile_position);

			//Check that the tile is not surrounded by walls (can be seen)
			if (!board_->IsSurroundedByWallsAt(tile_position)) {
				//Calculate the pixel position of each tile
				int pixel_x = tile_width * i;
				int pixel_y = tile_height * j;

				tile->draw(pixel_x, pixel_y, tile_width, tile_height);
			}
		}
	}

	//Draw entities after tiles
	for (int i = 0; i < entities.size(); i++) {
		ofPoint entity_position = entities[i]->GetPosition();

		//If entity is in the camera view, draw it
		if (entity_position.x >= position_.x &&
			entity_position.x < position_.x + width_ &&
			entity_position.y >= position_.y &&
			entity_position.y < position_.y + height_) {

			int pixel_x = tile_width * (entity_position.x - position_.x);
			int pixel_y = tile_height * (entity_position.y - position_.y);

			entities[i]->draw(pixel_x, pixel_y, tile_width, tile_height);
		}
	}
}

void Camera::update() {
	if (up_pressed_ && position_.y > 0) {
		position_.y--;
	}
	if (down_pressed_ && position_.y + height_ < Board::kBoardHeight) {
		position_.y++;
	}
	if (right_pressed_ && position_.x + width_ < Board::kBoardWidth) {
		position_.x++;
	}
	if (left_pressed_ && position_.x > 0) {
		position_.x--;
	}
}