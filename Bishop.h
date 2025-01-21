#pragma once
#include "Piece.h"
class Bishop : public Piece {
public:
	Bishop(char color, pair<int, int> coords);

	virtual Piece* clone() const override { return new Bishop(*this); }

	vector<pair<int, int>> getMoves(vector<vector<Piece*>>& checker) override;
};

