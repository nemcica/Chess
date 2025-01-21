#include "Rook.h"

Rook::Rook(char color, pair<int, int> coords) : Piece("Rk", color, coords) {

}

//Settters


//Getters
vector<pair<int, int>> Rook::getMoves(vector<vector<Piece*>>& checker) {
	int x = coords.first;
	int y = coords.second;
	vector<pair<int, int>> moves;
	
	for (int i = 1; i < 8; i++) {
		if (x + i < 8) {
			if (checker[y][x + i] == nullptr) moves.push_back(make_pair(x + i, y));
			else if (checker[y][x + i] != nullptr && checker[y][x + i]->getColor() == this->getColor()) break;
			else if (checker[y][x + i] != nullptr && checker[y][x + i]->getColor() != this->getColor()) {
				moves.push_back(make_pair(x + i, y));
				break;
			}
		}
	}
	for(int i = 1; i < 8; i++) {
		if (x - i >= 0) {
			if (checker[y][x - i] == nullptr) moves.push_back(make_pair(x - i, y));
			else if (checker[y][x - i] != nullptr && checker[y][x - i]->getColor() == this->getColor()) break;
			else if (checker[y][x - i] != nullptr && checker[y][x - i]->getColor() != this->getColor()) {
				moves.push_back(make_pair(x - i, y));
				break;
			}
		}
		
	}
	for (int i = 1; i < 8; i++) {
		if (y + i < 8) {
			if (checker[y + i][x] == nullptr) moves.push_back(make_pair(x, y + i));
			else if (checker[y + i][x] != nullptr && checker[y + i][x]->getColor() == this->getColor()) break;
			else if (checker[y + i][x] != nullptr && checker[y + i][x]->getColor() != this->getColor()) {
				moves.push_back(make_pair(x, y + i));
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		if (y - i >= 0) {
			if (checker[y - i][x] == nullptr) moves.push_back(make_pair(x, y - i));
			else if (checker[y - i][x] != nullptr && checker[y - i][x]->getColor() == this->getColor()) break;
			else if (checker[y - i][x] != nullptr && checker[y - i][x]->getColor() != this->getColor()) {
				moves.push_back(make_pair(x, y - i));
				break;
			}
		}
	}

	return moves;
}