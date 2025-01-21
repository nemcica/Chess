#include "Knight.h"

Knight::Knight(char color, pair<int, int> coords) : Piece("Kn", color, coords) {

}

vector<pair<int, int>> Knight::getMoves(vector<vector<Piece*>>& checker) {
	int x = coords.first;
	int y = coords.second;
	vector<pair<int, int>> moves;

	if (x + 2 < 8) {
		if (y + 1 < 8) {
			if (checker[y + 1][x + 2] == nullptr) moves.push_back(make_pair(x + 2, y + 1));
			else if (checker[y + 1][x + 2] != nullptr && this->getColor() != checker[y + 1][x + 2]->getColor()) moves.push_back(make_pair(x + 2, y + 1));
		}
		if (y - 1 >= 0) {
			if (checker[y - 1][x + 2] == nullptr) moves.push_back(make_pair(x + 2, y - 1));
			else if (checker[y - 1][x + 2] != nullptr && this->getColor() != checker[y - 1][x + 2]->getColor()) moves.push_back(make_pair(x + 2, y - 1));
		}
	}

	if (x - 2 >= 0) {
		if (y + 1 < 8) {
			if (checker[y + 1][x - 2] == nullptr) moves.push_back(make_pair(x - 2, y + 1));
			else if (checker[y + 1][x - 2] != nullptr && this->getColor() != checker[y + 1][x - 2]->getColor()) moves.push_back(make_pair(x - 2, y + 1));
		}
		if (y - 1 >= 0) {
			if (checker[y - 1][x - 2] == nullptr) moves.push_back(make_pair(x - 2, y - 1));
			else if (checker[y - 1][x - 2] != nullptr && this->getColor() != checker[y - 1][x - 2]->getColor()) moves.push_back(make_pair(x - 2, y - 1));
		}
	}

	if (y + 2 < 8) {
		if (x + 1 < 8) {
			if (checker[y + 2][x + 1] == nullptr) moves.push_back(make_pair(x + 1, y + 2));
			else if (checker[y + 2][x + 1] != nullptr && this->getColor() != checker[y + 2][x + 1]->getColor()) moves.push_back(make_pair(x + 1, y + 2));
		}
		if (x - 1 >= 0) {
			if (checker[y +2][x - 1] == nullptr) moves.push_back(make_pair(x - 1, y + 2));
			else if (checker[y + 2][x - 1] != nullptr && this->getColor() != checker[y + 2][x - 1]->getColor()) moves.push_back(make_pair(x - 1, y + 2));
		}
	}

	if (y - 2 >= 0) {
		if (x + 1 < 8) {
			if (checker[y - 2][x + 1] == nullptr) moves.push_back(make_pair(x + 1, y - 2));
			else if (checker[y - 2][x + 1] != nullptr && this->getColor() != checker[y - 2][x + 1]->getColor()) moves.push_back(make_pair(x + 1, y - 2));
		}
		if (x - 1 >= 0) {
			if (checker[y - 2][x - 1] == nullptr) moves.push_back(make_pair(x - 1, y - 2));
			else if (checker[y - 2][x - 1] != nullptr && this->getColor() != checker[y - 2][x - 1]->getColor()) moves.push_back(make_pair(x - 1, y - 2));
		}
	}

	

	return moves;
}