#pragma once
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include <stack>

class ChessArray {
public:
	static vector<vector<Piece*>> chessPieces;
    bool bcheck;
    bool wcheck;
    stack<string> check_coords;

public:
    ChessArray();

    ~ChessArray();

	//Setters
    void setAll();
    void setPawns();
    void setRooks();
    void setKnights();
    void setBishops();
    void setKings();
    void setQueens();

    //Getters
    Piece* getPiece(int x, int y);
    bool getKingCheck(char color);

    void check_wKing();
    void check_bKing();
    bool isValidMove(Piece* piece, pair<int, int> new_coords, char color);

    bool checkmate(char color);

    pair<char, int> convert_to_LN(pair<int, int> coords);
    pair<int, int> convert_to_NN(pair<char, int> coords);

    void handlePawnPromotion(Piece* pawn, string piece_name);
};
