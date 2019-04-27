#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/board.h"

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

	const Tile& tile = board.GetTileAt(0, 0);
	REQUIRE(tile.GetFloor().GetType() == Floor::Type::GRASS);
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

TEST_CASE("Floor Default Constructor") {
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