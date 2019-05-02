#include "ofMain.h"
#include "entity.h"
#pragma once

class Cat : public Entity
{
public:
	Cat();
	Cat(const ofPoint spawn_position);

	static void LoadTextures();

	void UpdateTurnAction(const Board& board);

private:
	static ofImage cat_1;

	Entity::Activity GetNewActivity(const Board& board);
	TurnAction CreateTurnAction(const Board& board);
	TurnAction CreateRandomMove();
	TurnAction CreateNextMove();
};