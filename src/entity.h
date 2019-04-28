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
	TurnAction& GetTurnAction();

	void SetPosition(const ofPoint position);

	//Pass in a reference to the current board so the entity can update its action
	virtual void UpdateTurnAction(const Board& board) = 0;

	void draw(int x, int y, int width, int height);

protected:
	ofImage* image_;
	TurnAction turn_action_;

private:
	ofPoint position_;

};