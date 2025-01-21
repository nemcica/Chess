#pragma once
#include "Piece.h"
class King : public Piece {

public:
	King(char color, pair<int, int> coords);

	virtual Piece* clone() const override { return new King(*this); }

	vector<pair<int, int>> getMoves(vector<vector<Piece*>>& checker) override;
};

