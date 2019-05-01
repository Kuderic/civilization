#include "camera.h"
#include "board.h"
#include "ofApp.h"

Camera::Camera() {
	width_ = kDefaultWidth;
	height_ = kDefaultHeight;
	pixel_width_ = ofGetWindowWidth();
	pixel_height_ = ofGetWindowHeight();
	position_ = ofPoint(0, 0, 0);
	board_ = nullptr;
}

ofPoint Camera::GetPosition() const {
	return position_;
}

//Called when mouse clicks
ofPoint Camera::GetTilePositionAt(int pixel_x, int pixel_y) const {
	int tile_width = pixel_width_ / width_;
	int tile_height = pixel_height_ / height_;
	int x = position_.x + pixel_x / tile_width;
	int y = position_.y + pixel_y / tile_height;

	return ofPoint(x, y, 0);
}

int Camera::GetWidth() const {
	return width_;
}

int Camera::GetHeight() const{
	return height_;
}

void Camera::SetBoard(const Board* board) {
	board_ = board;
}

void Camera::SetHeight(int height) {
	//Check that height isn't larger than board
	if (height >= Board::kBoardHeight) {
		height = Board::kBoardHeight - 1;
	} else if (height < 1) {
		height = 1;
	}
	height_ = height;

	//Make sure that position + height stays in bounds
	if (position_.y + height_ >= Board::kBoardHeight) {
		position_.y = Board::kBoardHeight - height_;
	}
}

void Camera::SetWidth(int width) {
	if (width >= Board::kBoardWidth) {
		width = Board::kBoardWidth - 1;
	} else if (width < 1) {
		width = 1;
	}
	width_ = width;

	//Make sure that position + width stays in bounds
	if (position_.x + width_ >= Board::kBoardWidth) {
		position_.x = Board::kBoardWidth - width_;
	}
}

void Camera::SetPixelHeight(int height) {
	pixel_height_ = height;
}

void Camera::SetPixelWidth(int width) {
	pixel_width_ = width;
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
	case '=':
		plus_pressed_ = true;
		break;
	case '-':
		minus_pressed_ = true;
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
	case '=':
		plus_pressed_ = false;
		break;
	case '-':
		minus_pressed_ = false;
		break;
	}
}

void Camera::draw() {
	//Calculate the width and height each tile should be drawn with
	int tile_width = pixel_width_ / width_;
	int tile_height = pixel_height_ / height_;

	//Iterate through tiles
	for (int i = 0; i < width_; i++) {
		for (int j = 0; j < height_; j++) {
			ofPoint tile_position = ofPoint(i + position_.x, j + position_.y);
			const Tile* tile = board_->GetTileAt(tile_position);

			//If tile has a wall, check if it is surrounded by walls
			if (tile->HasWall() && board_->IsSurroundedByWallsAt(tile_position)) {
				continue;
			}
			//Calculate the pixel position of each tile
			int pixel_x = tile_width * i;
			int pixel_y = tile_height * j;
			tile->draw(pixel_x, pixel_y, tile_width, tile_height);
		}
	}

	//Draw desginations
	const std::vector<Task>& tasks = board_->GetTasks();
	for (Task task : tasks) {
		const ofPoint task_position = task.GetPosition();

		if (PositionIsInView(task_position)) {
			int pixel_x = tile_width * (task_position.x - position_.x);
			int pixel_y = tile_height * (task_position.y - position_.y);
			task.draw(pixel_x, pixel_y, tile_width, tile_height);
		}
	}

	//Draw entities
	const std::vector<Entity*>& entities = board_->GetEntities();
	for (int i = 0; i < entities.size(); i++) {
		ofPoint entity_position = entities[i]->GetPosition();

		if (PositionIsInView(entity_position)) {
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

	if (plus_pressed_) {
		SetHeight(height_ - 1);
		SetWidth(width_ - 1);
	} else if (minus_pressed_) {
		SetHeight(height_ + 1);
		SetWidth(width_ + 1);
	}
}

bool Camera::PositionIsInView(const ofPoint position) const {
	return position.x >= position_.x &&
		position.x < position_.x + width_ &&
		position.y >= position_.y &&
		position.y < position_.y + height_;
}