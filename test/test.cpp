#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/board.h"

//========================================
// Board Class Tests
//========================================

TEST_CASE("Board Default Constructor") {
	ofSetupOpenGL(1600, 1200, OF_WINDOW);

	REQUIRE(0 == 0);
}

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

	int tile_width = ofGetWindowWidth() / Board::kBoardWidth;
	int tile_height = ofGetWindowHeight() / Board::kBoardHeight;

	int x = tile_width * 1;
	int y = tile_height * 3;

	const Tile& tile = board.GetTileAt(1, 3);
	REQUIRE(tile.GetPosition().x == x);
	REQUIRE(tile.GetPosition().y == y);
}


//========================================
// Tile Class Tests
//========================================

TEST_CASE("Tile Default Constructor") {
	Tile tile;
	REQUIRE(tile.GetPosition().x == 0);
}

TEST_CASE("Tile GetPosition()") {
	ofPoint point = ofPoint(10, 10, 0);

	Tile tile = Tile(point, 30, 40);

	REQUIRE(tile.GetPosition() == point);
}

TEST_CASE("Tile Specific Constructor") {
	ofPoint point = ofPoint(10, 10, 0);

	Tile tile = Tile(point, 30, 40);

	REQUIRE(tile.GetPosition() == point);

	REQUIRE(tile.GetWidth() == 30);
	REQUIRE(tile.GetHeight() == 40);
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