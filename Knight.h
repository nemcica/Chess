#pragma once
#include "Piece.h"
class Knight : public Piece {
public:
	Knight(char color, pair<int, int> coords);

	virtual Piece* clone() const override { return new Knight(*this); }

	vector<pair<int, int>> getMoves(vector<vector<Piece*>>& checker) override;
};

