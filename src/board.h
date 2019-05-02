#include "ofMain.h"
#include "tile.h"
#include "task.h"
#include "colonist.h"
#include "cat.h"
#include "sheep.h"
#include "chicken.h"

#include <vector>

#pragma once
class Board
{
public:
	//Board dimensions when setup.
	static const int kBoardWidth = 16 * 3;
	static const int kBoardHeight = 12 * 3;

	Board();
	~Board();

	const std::array<std::array<Tile, kBoardHeight>, kBoardWidth>& GetTiles() const;
	const std::vector<Entity*>& GetEntities() const;
	const std::vector<Task>& GetTasks() const;
	const Tile* GetTileAt(const ofPoint position) const;
	const Task* GetTaskAt(const ofPoint position) const;
	const vector<ofPoint> GetPath(const ofPoint start, const ofPoint destination) const;
	const vector<ofPoint> GetEmptyNeighborsAt(const ofPoint position) const;
	const vector<ofPoint> GetNeighborsAt(const ofPoint position) const;

	bool IsValidTile(ofPoint position) const;
	bool IsSurroundedByWallsAt(ofPoint position) const;

	void CreateWall(Wall::Type type, ofPoint position);
	void RemoveWall(ofPoint position);
	void CreateDigTask(ofPoint position);
	void RemoveTaskAt(ofPoint position);

	void setup();
	void update();
	//No draw() here. Set up a Camera object to the board for screen output

private:
	//Generate stone area at setup
	static const int kStoneGenWidth = 19;
	static const int kNumColonists = 10;
	static const int kNumCats = 3;
	static const int kNumSheep = 4;
	static const int kNumChickens = 6;

	std::array<std::array<Tile, kBoardHeight>, kBoardWidth> tiles_;
	std::vector<Entity*> entities_;
	std::vector<Task> tasks_;

	void GenerateTiles();
	//Can make the below into a function which takes Floor::Type and a generative function
	void CreateGrass();
	void CreateStone();

	void CreateColonists();
	void CreateAnimals();


	//=======	FOR PATHING ALGORITHM	========
	// A star algorithm taken from: https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h

	//	Node to star f, g, h values for A* pathing algorithm
	struct AStarNode {
		int y;
		int x;
		int parent_x;
		int parent_y;
		float g_cost;
		float h_cost;
		float f_cost;

		bool operator < (const AStarNode& rhs);
	};

	vector<ofPoint> MakePath(ofPoint start, ofPoint destination,
		std::array<std::array<AStarNode, kBoardHeight>, kBoardWidth> a_star_map) const;
	double CalculateH(ofPoint calculate, ofPoint destination) const;

};

