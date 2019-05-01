#include "board.h"

Board::Board() {
}

const std::array<std::array<Tile, Board::kBoardHeight>, Board::kBoardWidth>& Board::GetTiles() const {
	return tiles_;
}

const std::vector<Entity*>& Board::GetEntities() const {
	return entities_;
}

const Tile* Board::GetTileAt(ofPoint position) const {
	int x = position.x;
	int y = position.y;

	if (x < 0 || x >= kBoardWidth || y < 0 || y >= kBoardHeight) {
		return nullptr;
	}

	return &tiles_[x][y];
}

//Check the 8 surrounding tiles. If all neighboring tiles have walls, return true
bool Board::IsSurroundedByWallsAt(ofPoint position) const {
	int x = position.x;
	int y = position.y;

	for (int i = x - 1; i < x + 2; i++) {
		for (int j = y - 1; j < y + 2; j++) {
			//Skip over self
			if (i == x && j == y) {
				continue;
			}
			const Tile* neighbor = GetTileAt(ofPoint(i, j));

			//Check that neighbor exists (for edge tiles)
			if (!neighbor) {
				continue;
			} else if (!neighbor->HasWall()) {
				return false;
			}
		}
	}
	return true;
}

//Generate gameboard
void Board::setup() {
	InitAStarMap();

	GenerateTiles();
	CreateGrass();
	CreateStone();

	CreateColonists();
}

void Board::update() {
	for (int i = 0; i < entities_.size(); i++) {
		Entity& entity = *entities_[i];

		//Give entity a reference to board so it can update its action
		entity.UpdateTurnAction(*this);

		TurnAction& action = entity.GetTurnAction();
		/* Parse action for entity if done
			Note: I handle parsing in Board because board is the only class that has access to everything
			E.g. if action is digging a wall, board can remove the wall when action is complete*/
		if (action.IsComplete()) {
			switch (action.GetAction()) {
			case Action::MOVE:
				entity.SetPosition(action.GetTarget());
			}
		}
	}
}

//Called by camera when a tile is clicked
void Board::TileClicked(const ofPoint position) {
	int x = position.x;
	int y = position.y;
	//Check that x, y is part of the board
	if (x < kBoardWidth && y < kBoardHeight) {
		tiles_[x][y].SetWall(Wall(Wall::Type::EMPTY));
	}
}

void Board::GenerateTiles() {
	//Generate a kBoardWidth by kBoardHeight sized tile board
	for (int i = 0; i < kBoardWidth; i++) {
		for (int j = 0; j < kBoardHeight; j++) {
			Tile new_tile = Tile();
			tiles_[i][j] = new_tile;
		}
	}
}

void Board::CreateGrass() {
	//Generate grass on every board tile
	for (int i = 0; i < kBoardWidth; i++) {
		for (int j = 0; j < kBoardHeight; j++) {
			tiles_[i][j].SetFloor(Floor(Floor::Type::GRASS));
		}
	}
}

void Board::CreateStone() {
	//Generate stone in the bottom right corner (for now)
	for (int i = kBoardWidth - kStoneGenWidth; i < kBoardWidth; i++) {
		for (int j = kBoardHeight - kStoneGenWidth; j < kBoardHeight; j++) {
			tiles_[i][j].SetFloor(Floor(Floor::Type::STONE));
			tiles_[i][j].SetWall(Wall(Wall::Type::COBBLESTONE));
		}
	}
}

void Board::CreateColonists() {
	for (int i = 0; i < kNumColonists; i++) {
		Colonist* colonist = new Colonist(ofPoint(i, 0, 0));
		entities_.push_back(colonist);
	}
}


//=======	FOR PATHING ALGORITHM	========
// A star algorithm taken from: https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h

bool Board::AStarNode::operator < (const AStarNode& rhs) {
	return this->f_cost < rhs.f_cost;
}

void Board::InitAStarMap() {
	//Initialize a_star_map
	for (int x = 0; x < kBoardWidth; x++) {
		for (int y = 0; y < kBoardHeight; y++) {
			a_star_map[x][y].f_cost = FLT_MAX;
			a_star_map[x][y].g_cost = FLT_MAX;
			a_star_map[x][y].h_cost = FLT_MAX;
			a_star_map[x][y].parent_x = -1;
			a_star_map[x][y].parent_y = -1;
			a_star_map[x][y].x = x;
			a_star_map[x][y].y = y;
		}
	}
}

const std::vector<ofPoint> Board::GetPath(const ofPoint start, const ofPoint destination) {
	using namespace std;
	vector<ofPoint> empty;

	//Check that destination does not have a wall
	if (GetTileAt(destination)->HasWall()) {
		cout << "Destination is blocked" << endl;
		return empty;
	} else if (start == destination) {
		cout << "You are the destination" << endl;
		return empty;
	}

	bool closed_list[kBoardWidth][kBoardHeight] = { false };

	//Initialize our starting list
	int x = start.x;
	int y = start.y;
	a_star_map[x][y].f_cost = 0.0;
	a_star_map[x][y].g_cost = 0.0;
	a_star_map[x][y].h_cost = 0.0;
	a_star_map[x][y].parent_x = x;
	a_star_map[x][y].parent_y = y;

	vector<AStarNode> open_list;
	open_list.emplace_back(a_star_map[x][y]);
	bool destination_found = false;

	while (!open_list.empty() && open_list.size() < kBoardWidth * kBoardHeight) {
		AStarNode node;
		do {
			//Can improve performance by making vector into a set
			float temp = FLT_MAX;
			vector<AStarNode>::iterator node_it;
			for (vector<AStarNode>::iterator it = open_list.begin();
				it != open_list.end(); it = next(it)) {
				AStarNode n = *it;
				if (n.f_cost < temp) {
					temp = n.f_cost;
					node_it = it;
				}
			}
			node = *node_it;
			open_list.erase(node_it);
			//Do this until it finds a non-wall tile
		} while (GetTileAt(ofPoint(node.x, node.y))->HasWall());

		x = node.x;
		y = node.y;
		closed_list[x][y] = true;

		//For each neighbour starting from North-West to South-East
		for (int new_x = -1; new_x <= 1; new_x++) {
			for (int new_y = -1; new_y <= 1; new_y++) {
				int neighbor_x = x + new_x;
				int neighbor_y = y + new_y;
				//Make sure neighboring tile is valid
				if (neighbor_x < 0 || neighbor_x >= kBoardWidth || neighbor_y < 0 || neighbor_y >= kBoardHeight) {
					continue;
				}

				double new_g, new_h, new_f;

				if (GetTileAt(ofPoint(neighbor_x, neighbor_y))->HasWall() == false) {
					if (destination == ofPoint(neighbor_x, neighbor_y)) {
						//Destination found - make path
						a_star_map[neighbor_x][neighbor_y].parent_x = x;
						a_star_map[neighbor_x][neighbor_y].parent_y = y;
						destination_found = true;
						return MakePath(start, destination);
					}

					else if (closed_list[neighbor_x][neighbor_y] == false) {
						new_g = node.g_cost + 1.0;
						new_h = CalculateH(ofPoint(neighbor_x, neighbor_y), destination);
						new_f = new_g + new_h;

						// Check if this path is better than the one already present
						if (a_star_map[neighbor_x][neighbor_y].f_cost == FLT_MAX ||
							a_star_map[neighbor_x][neighbor_y].f_cost > new_f) {
							// Update the details of this neighbour AStarNode
							a_star_map[neighbor_x][neighbor_y].f_cost = new_f;
							a_star_map[neighbor_x][neighbor_y].g_cost = new_g;
							a_star_map[neighbor_x][neighbor_y].h_cost = new_h;
							a_star_map[neighbor_x][neighbor_y].parent_x = x;
							a_star_map[neighbor_x][neighbor_y].parent_y = y;
							open_list.emplace_back(a_star_map[x + new_x][neighbor_y]);
						}
					}
				}
			}
		}
	}
	if (destination_found == false) {
		cout << "Destination not found" << endl;
		return empty;
	}

}

vector<ofPoint> Board::MakePath(ofPoint start, ofPoint destination) {
	try {
		cout << "Found a path" << endl;
		int x = destination.x;
		int y = destination.y;
		std::stack<AStarNode> path;
		std::vector<ofPoint> usable_path;

		while (!(a_star_map[x][y].parent_x == x && a_star_map[x][y].parent_y == y)
			&& a_star_map[x][y].x != -1 && a_star_map[x][y].y != -1) {
			path.push(a_star_map[x][y]);
			int temp_x = a_star_map[x][y].parent_x;
			int temp_y = a_star_map[x][y].parent_y;
			x = temp_x;
			y = temp_y;
		}
		path.push(a_star_map[x][y]);

		//Turn AStarNode into ofPoint
		while (!path.empty()) {
			AStarNode top = path.top();
			ofPoint top_position = ofPoint(top.x, top.y);
			path.pop();

			usable_path.emplace_back(top_position);
		}
		return usable_path;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

//Calculate distance from "calculate" to destination for heuristic
double Board::CalculateH(ofPoint calculate, ofPoint destination) {
	double H = (sqrt((calculate.x - destination.x)*(calculate.x - destination.x)
		+ (calculate.y - destination.y)*(calculate.y - destination.y)));
	return H;
}