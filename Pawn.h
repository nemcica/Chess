#pragma once
#include "Piece.h"

class Pawn : public Piece {
private:
	pair<int, int> startcoords;
	bool firstmove;

public:
	Pawn(char color, pair<int, int> coords);

	virtual Piece* clone() const override { return new Pawn(*this); }

	vector<pair<int, int>> getMoves(vector<vector<Piece*>>& checker) override;
	
	void checkFirstMove();

};

