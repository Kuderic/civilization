#include "ofMain.h"
#include "turn_action.h"
#pragma once

class Board;
//This is an abstract class
class Entity
{
public:
	Entity();
	Entity(const ofPoint position);

	const ofPoint GetPosition() const;
	const ofImage* GetImage() const;

	void SetPosition(int x, int y);

	//Pass in a reference to the current board so the entity can make an action
	virtual TurnAction GetTurnAction(const Board& board) = 0;

	void draw(int x, int y, int width, int height);

protected:
	ofImage* image_;
private:
	ofPoint position_;

};