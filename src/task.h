#include "ofMain.h"
#pragma once

class Task {
public:
	enum class Type {
		DIG
	};

	Task(Type type, ofPoint position);

	Type GetType() const;
	ofPoint GetPosition() const;

private:
	Type type_;
	ofPoint position_;
};