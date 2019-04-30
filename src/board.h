#include "ofMain.h"
#include "tile.h"
#include "colonist.h"

#include <vector>

#pragma once
class Board
{
public:
	//Board dimensions when setup.
	static const int kBoardWidth = 16 * 3;
	static const int kBoardHeight = 12 * 3;

	Board();

	const std::array<std::array<Tile, kBoardHeight>, kBoardWidth>& GetTiles() const;
	const std::vector<Entity*>& GetEntities() const;
	const Tile* GetTileAt(ofPoint position) const;
	bool IsSurroundedByWallsAt(ofPoint position) const;

	void setup();
	void update();
	//No draw() here. Set up a Camera object to the board for screen output

	void TileClicked(ofPoint position);

private:
	//Generate stone area at setup
	static const int kStoneGenWidth = 13;
	static const int kNumColonists = 1;

	std::vector<Entity*> entities_;
	std::array<std::array<Tile, kBoardHeight>, kBoardWidth> tiles_;

	void GenerateTiles();
	//Can make the below into a function which takes Floor::Type and a generative function
	void CreateGrass();
	void CreateStone();

	void CreateColonists();
};

