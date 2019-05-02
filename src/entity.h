#include "ofMain.h"
#include "turn_action.h"
#pragma once

class Board;
class Task;

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
	static void RemoveTask(const Task* task);

	//Pass in a reference to the current board so the entity can update its action
	virtual void UpdateTurnAction(const Board& board) = 0;

	void draw(int x, int y, int width, int height);

protected:
	enum class Activity {
		IDLE,
		WALKING,
		DIGGING,
		BUILDING
	};
	static unordered_map<const Task*, const Entity*> task_map_;

	ofImage* image_;
	TurnAction turn_action_;
	Activity activity_;

	//	Store current path. Only update periodically or if a tile in the path becomes a wall.
	std::vector<ofPoint> current_path_;
	ofPoint action_tile_; //Tile to perform action on

private:
	ofPoint position_;
};