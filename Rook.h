#pragma once
#include "Piece.h"

class Rook : public Piece {

public:
	Rook(char color, pair<int, int> coords);

	virtual Piece* clone() const override { return new Rook(*this); }

	//Setters

	//Getters
	vector<pair<int, int>> getMoves(vector<vector<Piece*>>& checker) override;



};

