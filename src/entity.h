#include "ofMain.h"
#pragma once

//This is an abstract class
class Entity
{
public:
	Entity();
	Entity(const ofPoint position);

	const ofPoint GetPosition() const;
	const ofImage* GetImage() const;

	//Not sure what should be in charge of moving entities
	//The entity itself, the board, or something else?
	void SetPosition(int x, int y);

	virtual void update() = 0;
	void draw(int x, int y, int width, int height);

protected:
	ofImage* image_;
	ofPoint position_;

};