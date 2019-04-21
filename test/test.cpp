#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/board.h"
#include "../src/tile.h"

//========================================
// Board Class Tests
//========================================

TEST_CASE("Board Default Constructor") {
	REQUIRE(0 == 0);
}

TEST_CASE("Board setup()") {
	Board board;
	board.setup(50, 50);
	REQUIRE(board.tiles.size() == 10);
}



//========================================
// Tile Class Tests
//========================================

TEST_CASE("Tile Default Constructor") {
	REQUIRE(0 == 0);
}

TEST_CASE("Tile Position Constructor") {
	ofPoint point = ofPoint(10, 10, 0);
	ofImage image;
	image.load("../resources/grass_tile_1");

	Tile new_tile = Tile(point, 30, 40, &image);

	REQUIRE(new_tile.position.x == 10);
	REQUIRE(new_tile.position.y == 10);
	REQUIRE(new_tile.position.z == 0);

	REQUIRE(new_tile.GetWidth() == 30);
	REQUIRE(new_tile.GetHeight() == 40);
}

TEST_CASE("Tile setup()") {
	REQUIRE(0 == 0);
}