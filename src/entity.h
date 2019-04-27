#include "ofMain.h"
#pragma once
class Entity
{
public:
	Entity();
	Entity(const ofPoint position);

	const ofPoint GetPosition() const;
	const ofImage* GetImage() const;

	//Not sure if I should have SetPosition or MoveDirection methods
	void SetPosition(int x, int y);

	virtual void update();
	void draw(int x, int y, int width, int height);

protected:
	ofImage* image_;

private:
	ofPoint position_;
};