#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/board.h"
#include "../src/camera.h"

//========================================
// Board Class Tests
//========================================

TEST_CASE("Board setup()") {
	ofSetupOpenGL(1600, 1200, OF_WINDOW);
	Board board;
	board.setup();

	REQUIRE(board.GetTiles().size() == Board::kBoardWidth);
	REQUIRE(board.GetTiles()[0].size() == Board::kBoardHeight);
}

TEST_CASE("Board GetTileAt()") {
	ofSetupOpenGL(1600, 1200, OF_WINDOW);
	Board board;
	board.setup();

	const Tile* tile = board.GetTileAt(ofPoint(0, 0));
	REQUIRE(tile->GetFloor().GetType() == Floor::Type::GRASS);
}

TEST_CASE("Board GetTileAt() Invalid") {
	ofSetupOpenGL(1600, 1200, OF_WINDOW);
	Board board;
	board.setup();

	const Tile* tile = board.GetTileAt(ofPoint(-1, -1));
	REQUIRE(tile == nullptr);
	tile = board.GetTileAt(ofPoint(Board::kBoardWidth, 0));
	REQUIRE(tile == nullptr);
	tile = board.GetTileAt(ofPoint(0, Board::kBoardHeight));
	REQUIRE(tile == nullptr);
}


//========================================
// Tile Class Tests
//========================================

TEST_CASE("Tile Default Constructor") {
	Tile tile;
	REQUIRE(tile.GetFloor().GetType() == Floor::Type::GRASS);
}

TEST_CASE("Tile GetFloor()") {
	Tile tile;
	REQUIRE(tile.GetFloor().GetType() == Floor::Type::GRASS);
}

TEST_CASE("Tile GetWall()") {
	Tile tile;
	REQUIRE(tile.GetWall().GetType() == Wall::Type::EMPTY);
}

TEST_CASE("Tile SetFloor()") {
	Tile tile;
	tile.SetFloor(Floor(Floor::Type::STONE));

	REQUIRE(tile.GetFloor().GetType() == Floor::Type::STONE);
}

TEST_CASE("Tile SetWall()") {
	Tile tile;
	tile.SetWall(Wall(Wall::Type::STONE_BRICK));

	REQUIRE(tile.GetWall().GetType() == Wall::Type::STONE_BRICK);
}


//========================================
// Floor Class Tests
//========================================

TEST_CASE("Floor Default Constructor") {
	Floor floor;
	REQUIRE(floor.GetType() == Floor::Type::GRASS);
}

TEST_CASE("Floor Type Constructor") {
	Floor grass(Floor::Type::GRASS);
	Floor stone(Floor::Type::STONE);

	REQUIRE(grass.GetType() == Floor::Type::GRASS);
	REQUIRE(stone.GetType() == Floor::Type::STONE);
}

TEST_CASE("Floor GetType()") {
	Floor grass(Floor::Type::GRASS);

	REQUIRE(grass.GetType() == Floor::Type::GRASS);
}


//========================================
// Wall Class Tests
//========================================

TEST_CASE("Wall Default Constructor") {
	Wall Wall;
	REQUIRE(Wall.GetType() == Wall::Type::STONE_BRICK);
}

TEST_CASE("Wall Type Constructor") {
	Wall wood(Wall::Type::WOOD_PLANKS);

	REQUIRE(wood.GetType() == Wall::Type::WOOD_PLANKS);
}

TEST_CASE("Wall GetType()") {
	Wall wood(Wall::Type::WOOD_PLANKS);

	REQUIRE(wood.GetType() == Wall::Type::WOOD_PLANKS);
}


//========================================
// Entity Class Tests
//========================================

//Entity is an abstract class, so I can only test it as a pointer/reference to a subclass
TEST_CASE("Entity Colonist Polymorphism") {
	Colonist colonist = Colonist(ofPoint(2, 3, 0));
	Entity& entity = colonist;

	REQUIRE(entity.GetPosition() == ofPoint(2, 3, 0));
}

TEST_CASE("Entity Colonist Poly Constructor") {
	Entity& entity = Colonist(ofPoint(2, 3, 0));

	REQUIRE(entity.GetPosition() == ofPoint(2, 3, 0));
}


//========================================
// Colonist Class Tests
//========================================

TEST_CASE("Colonist Default Constructor") {
	Colonist colonist;
	REQUIRE(colonist.GetPosition() == ofPoint(0, 0, 0));
}

TEST_CASE("Colonist GetPosition()") {
	Colonist colonist(ofPoint(1, 2, 3));

	REQUIRE(colonist.GetPosition() == ofPoint(1, 2, 3));
}

TEST_CASE("Colonist GetImage()") {
	Colonist colonist;

	//GetImage should never return nullptr
	REQUIRE(colonist.GetImage() != nullptr);
}

TEST_CASE("Colonist GetTurnAction()") {
	Colonist colonist;

	REQUIRE(colonist.GetTurnAction().GetAction() == Action::NONE);
}

TEST_CASE("Colonist SetPosition()") {
	Colonist colonist;
	colonist.SetPosition(ofPoint(3, 5, 6));

	REQUIRE(colonist.GetPosition() == ofPoint(3, 5, 6));
}


//========================================
// TurnAction Class Tests
//========================================

TEST_CASE("TurnAction Default Constructor") {
	TurnAction turn_action;

	REQUIRE(turn_action.GetAction() == Action::NONE);
}

TEST_CASE("TurnAction Specific Constructor") {
	TurnAction turn_action = TurnAction(Action::NONE, ofPoint(0, 0, 0));

	REQUIRE(turn_action.GetAction() == Action::NONE);
	REQUIRE(turn_action.GetTarget() == ofPoint(0, 0, 0));
}

TEST_CASE("TurnAction GetAction()") {
	TurnAction turn_action = TurnAction(Action::DIG, ofPoint(0, 0, 0));

	REQUIRE(turn_action.GetAction() == Action::DIG);
}

TEST_CASE("TurnAction GetTarget()") {
	TurnAction turn_action = TurnAction(Action::NONE, ofPoint(1, 0, 0));

	REQUIRE(turn_action.GetTarget() == ofPoint(1, 0, 0));
}

TEST_CASE("TurnAction GetProgress()") {
	TurnAction turn_action = TurnAction(Action::NONE, ofPoint(0, 0, 0));

	REQUIRE(turn_action.GetProgress() == 0);
}

TEST_CASE("TurnAction IncrementProgress()") {
	TurnAction turn_action = TurnAction(Action::NONE, ofPoint(0, 0, 0));
	turn_action.IncrementProgress();

	REQUIRE(turn_action.GetProgress() != 0);
}

TEST_CASE("TurnAction IncrementProgress() Past Max") {
	TurnAction turn_action = TurnAction(Action::NONE, ofPoint(0, 0, 0));

	for (int i = 0; i < 9999; i++) {
		turn_action.IncrementProgress();
	}

	REQUIRE(turn_action.IsComplete());
}

TEST_CASE("TurnAction operator++") {
	TurnAction turn_action = TurnAction(Action::NONE, ofPoint(0, 0, 0));
	++turn_action;

	REQUIRE(turn_action.GetProgress() != 0);
}


//========================================
// Camera Class Tests
//========================================

TEST_CASE("Camera Default Constructor") {
	ofSetupOpenGL(1600, 1200, OF_WINDOW);
	Camera camera;

	REQUIRE(camera.GetHeight() == Camera::kDefaultHeight);
}


//========================================
// Task Class Tests
//========================================

TEST_CASE("Task Default Constructor") {
	Task task = Task(Task::Type::DIG, ofPoint(0, 0));

	REQUIRE(task.GetPosition() == ofPoint(0, 0));
	REQUIRE(task.GetType() == Task::Type::DIG);
}

//========================================
// A* Pathing Algorithm Tests
//========================================

TEST_CASE("Basic Pathing Test") {
	ofSetupOpenGL(1600, 1200, OF_WINDOW);
	Board board;
	board.setup();

	std::vector<ofPoint> path = board.GetPath(ofPoint(0, 0), ofPoint(5, 5));

	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i] << std::endl;
	}
}