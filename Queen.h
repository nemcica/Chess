#pragma once
#include "Piece.h"
class Queen : public Piece {
public:
	Queen(char color, pair<int, int> coords);

	virtual Piece* clone() const override { return new Queen(*this); }

	vector<pair<int, int>> getMoves(vector<vector<Piece*>>& checker) override;
};

