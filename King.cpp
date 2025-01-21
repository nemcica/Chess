#include "King.h"

King::King(char color, pair<int, int> coords) : Piece("Kg", color, coords) {

}

vector<pair<int, int>> King::getMoves(vector<vector<Piece*>>& checker) {
	int x = coords.first;
	int y = coords.second;
	vector<pair<int, int>> moves;

	if (x + 1 < 8) {
		if (checker[y][x + 1] == nullptr) moves.push_back(make_pair(x + 1, y));
		if (checker[y][x + 1] != nullptr && this->getColor() != checker[y][x + 1]->getColor()) moves.push_back(make_pair(x + 1, y));

		if (y + 1 < 8) {
			if (checker[y + 1][x + 1] == nullptr) moves.push_back(make_pair(x + 1, y + 1));
			if (checker[y + 1][x + 1] != nullptr && this->getColor() != checker[y + 1][x + 1]->getColor()) moves.push_back(make_pair(x + 1, y + 1));
		}
		if (y - 1 >= 0) {
			if (checker[y - 1][x + 1] == nullptr) moves.push_back(make_pair(x + 1, y - 1));
			if (checker[y - 1][x + 1] != nullptr && this->getColor() != checker[y - 1][x + 1]->getColor()) moves.push_back(make_pair(x + 1, y - 1));
		}
	}

	if (x - 1 >= 0) {
		if (checker[y][x - 1] == nullptr) moves.push_back(make_pair(x - 1, y));
		if (checker[y][x - 1] != nullptr && this->getColor() != checker[y][x - 1]->getColor()) moves.push_back(make_pair(x - 1, y));

		if (y + 1 < 8) {
            if (checker[y + 1][x - 1] == nullptr) moves.push_back(make_pair(x - 1, y + 1));
			if (checker[y + 1][x - 1] != nullptr && this->getColor() != checker[y + 1][x - 1]->getColor()) moves.push_back(make_pair(x - 1, y + 1));
		}
		if (y - 1 >= 0) {
			if (checker[y - 1][x - 1] == nullptr) moves.push_back(make_pair(x - 1, y - 1));
			if (checker[y - 1][x - 1] != nullptr && this->getColor() != checker[y - 1][x - 1]->getColor()) moves.push_back(make_pair(x - 1, y - 1));
		}
	}

	if (y + 1 < 8) {
		if (checker[y + 1][x] == nullptr) moves.push_back(make_pair(x, y + 1));
		if (checker[y + 1][x] != nullptr && this->getColor() != checker[y + 1][x]->getColor()) moves.push_back(make_pair(x, y + 1));
	}

	if (y - 1 >= 0) {
		if (checker[y - 1][x] == nullptr) moves.push_back(make_pair(x, y - 1));
		if (checker[y - 1][x] != nullptr && this->getColor() != checker[y - 1][x]->getColor()) moves.push_back(make_pair(x, y - 1));
	}

	return moves;
}
