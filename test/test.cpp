#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/board.h"
#include "../src/tile.h"

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
	ofImage image;
	image.load("../resources/grass_tile_1");
	Tile tile = Tile(point, 30, 40, &image);

	REQUIRE(tile.GetPosition() == point);
}

TEST_CASE("Tile Specific Constructor") {
	ofPoint point = ofPoint(10, 10, 0);
	ofImage image;
	image.load("../resources/grass_tile_1");
	Tile tile = Tile(point, 30, 40, &image);

	REQUIRE(tile.GetPosition() == point);

	REQUIRE(tile.GetWidth() == 30);
	REQUIRE(tile.GetHeight() == 40);
}