#include "Bishop.h"

Bishop::Bishop(char color, pair<int, int> coords) : Piece("Bs", color, coords) {

}

vector<pair<int, int>> Bishop::getMoves(vector<vector<Piece*>>& checker) {
	int x = coords.first;
	int y = coords.second;
	vector<pair<int, int>> moves;

	for (int i = 1; i < 8; i++) {
		if (x + i < 8 && y + i < 8) {
			if (checker[y + i][x + i] == nullptr) moves.push_back(make_pair(x + i, y + i));
			else if (checker[y + i][x + i] != nullptr && this->getColor() == checker[y + i][x + i]->getColor()) break;
			else if (checker[y + i][x + i] != nullptr && this->getColor() != checker[y + i][x + i]->getColor()) {
				moves.push_back(make_pair(x + i, y + i));
				break;
			}	
		}
	}

	for (int i = 1; i < 8; i++) {
		if (x + i < 8 && y - i >= 0) {
			if (checker[y - i][x + i] == nullptr) moves.push_back(make_pair(x + i, y - i));
			else if (checker[y - i][x + i] != nullptr && this->getColor() == checker[y - i][x + i]->getColor()) break;
			else if (checker[y - i][x + i] != nullptr && this->getColor() != checker[y - i][x + i]->getColor()) {
				moves.push_back(make_pair(x + i, y - i));
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		if (x - i >= 0 && y + i < 8) {
			if (checker[y + i][x - i] == nullptr) moves.push_back(make_pair(x - i, y + i));
			else if (checker[y + i][x - i] != nullptr && this->getColor() == checker[y + i][x - i]->getColor()) break;
			else if (checker[y + i][x - i] != nullptr && this->getColor() != checker[y + i][x - i]->getColor()) {
				moves.push_back(make_pair(x - i, y + i));
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		if (x - i >= 0 && y - i >= 0) {
			if (checker[y - i][x - i] == nullptr) moves.push_back(make_pair(x - i, y - i));
			else if (checker[y - i][x - i] != nullptr && this->getColor() == checker[y - i][x - i]->getColor()) break;
			else if (checker[y - i][x - i] != nullptr && this->getColor() != checker[y - i][x - i]->getColor()) {
				moves.push_back(make_pair(x - i, y - i));
				break;
			}
		}
	}

	return moves;
}