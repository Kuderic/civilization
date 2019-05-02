#include "ofMain.h"
#pragma once

class Entity;
class Task {
public:
	enum class Type {
		DIG
	};

	Task(Type type, ofPoint position);

	Type GetType() const;
	ofPoint GetPosition() const;

	void draw(int x, int y, int width, int height) const;
	static void LoadTextures();

private:
	Type type_;
	ofPoint position_;

	//Task textures
	static ofImage dig;
};