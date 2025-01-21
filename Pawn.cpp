#include "Pawn.h"

Pawn::Pawn(char color, pair<int, int> coords) : Piece("Pw", color, coords) {
	startcoords = coords;
	firstmove = true;
}


vector<pair<int,int>> Pawn::getMoves(vector<vector<Piece*>>& checker) {
	checkFirstMove();
	int x = coords.first;
	int y = coords.second;
	vector<pair<int, int>> moves;

    if (checker[y][x]->getColor() == 'b' && y + 1 < 8) {
		if (firstmove) {
            if (checker[y + 2][x] == nullptr && checker[y + 1][x] == nullptr) moves.push_back(make_pair(x, y + 2));
		}
		if (checker[y + 1][x] == nullptr) moves.push_back(make_pair(x, y + 1));

		if (x + 1 < 8 && y + 1 < 8) {
			if (checker[y + 1][x + 1] != nullptr && checker[y + 1][x + 1]->getColor() != this->getColor()) moves.push_back(make_pair(x + 1, y + 1));
		}
        if (x - 1 >= 0 && y + 1 < 8) {
            if (checker[y + 1][x - 1] != nullptr && checker[y + 1][x - 1]->getColor() != this->getColor()) moves.push_back(make_pair(x - 1, y + 1));
        }
	}

    if (checker[y][x]->getColor() == 'w' && y - 1 >= 0) {
		if (firstmove) {
            if (checker[y - 2][x] == nullptr && checker[y - 1][x] == nullptr) moves.push_back(make_pair(x, y - 2));
		}
		if (checker[y - 1][x] == nullptr) moves.push_back(make_pair(x, y - 1));

		if (x - 1 >= 0 && y - 1 >= 0) {
			if (checker[y - 1][x - 1] != nullptr && checker[y - 1][x - 1]->getColor() != this->getColor()) moves.push_back(make_pair(x - 1, y - 1));
		}
        if (x + 1 < 8 && y - 1 >= 0) {
            if (checker[y - 1][x + 1] != nullptr && checker[y - 1][x + 1]->getColor() != this->getColor()) moves.push_back(make_pair(x + 1, y - 1));
        }
	}
	return moves;
}

void Pawn::checkFirstMove() {
	if (coords != startcoords) firstmove = false;
}

