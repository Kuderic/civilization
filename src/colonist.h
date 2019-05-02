#include "ofMain.h"
#include "entity.h"
#pragma once

class Colonist : public Entity
{
public:
	Colonist();
	Colonist(const ofPoint spawn_position);

	static void LoadTextures();

	void UpdateTurnAction(const Board& board);

private:
	static ofImage dog_1;

	Entity::Activity GetNewActivity(const Board& board);
	TurnAction CreateTurnAction(const Board& board);
	TurnAction CreateRandomMove();
	TurnAction CreateNextMove();
};