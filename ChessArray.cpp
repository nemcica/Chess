#include "ChessArray.h"
#include <sstream>

ChessArray::ChessArray() : bcheck(false), wcheck(false), check_coords(stack<string>()) {
    setAll();
}


ChessArray::~ChessArray() {
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            if(chessPieces[i][j]!=nullptr) delete chessPieces[i][j];
            chessPieces[i][j] = nullptr;
        }
    }
}

//Setters
void ChessArray::setAll() {
    setPawns();
    setRooks();
    setKnights();
    setBishops();
    setKings();
    setQueens();
}

void ChessArray::setPawns() {
    for (int i = 0; i < 8; i++) {
        chessPieces[1][i] = new Pawn('b', make_pair(i, 1));
        chessPieces[6][i] = new Pawn('w', make_pair(i, 6));
    }
}

void ChessArray::setRooks() {
    chessPieces[0][0] = new Rook('b', make_pair(0, 0));
    chessPieces[0][7] = new Rook('b', make_pair(7, 0));
    chessPieces[7][0] = new Rook('w', make_pair(0, 7));
    chessPieces[7][7] = new Rook('w', make_pair(7, 7));
}

void ChessArray::setKnights() {
    chessPieces[0][1] = new Knight('b', make_pair(1, 0));
    chessPieces[0][6] = new Knight('b', make_pair(6, 0));
    chessPieces[7][1] = new Knight('w', make_pair(1, 7));
    chessPieces[7][6] = new Knight('w', make_pair(6, 7));

}

void ChessArray::setBishops() {
    chessPieces[0][2] = new Bishop('b', make_pair(2, 0));
    chessPieces[0][5] = new Bishop('b', make_pair(5, 0));
    chessPieces[7][2] = new Bishop('w', make_pair(2, 7));
    chessPieces[7][5] = new Bishop('w', make_pair(5, 7));
}

void ChessArray::setKings() {
    chessPieces[0][4] = new King('b', make_pair(4, 0));
    chessPieces[7][4] = new King('w', make_pair(4, 7));
}

void ChessArray::setQueens() {
    chessPieces[0][3] = new Queen('b', make_pair(3, 0));
    chessPieces[7][3] = new Queen('w', make_pair(3, 7));
}



//Getters
Piece* ChessArray::getPiece(int x, int y) {
    return chessPieces[y][x];
}

bool ChessArray::getKingCheck(char color) {
    if (color == 'w') return wcheck;
    else if (color == 'b') return bcheck;
}

void ChessArray::check_wKing() {
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {

            if (chessPieces[b][a] != nullptr) {
                if (chessPieces[b][a]->getName() == "wKg") {
                    pair<int, int> king_coords = chessPieces[b][a]->getCoords();
                    int counter = 0;

                    for (int i = 7; i >= 0; i--) {
                        for (int j = 7; j >= 0; j--) {
                            if (chessPieces[j][i] != nullptr) {
                                if (chessPieces[j][i]->getColor() != chessPieces[b][a]->getColor() && chessPieces[j][i]->getMoves(chessPieces).size() > 0) {
                                    for (auto move : chessPieces[j][i]->getMoves(chessPieces)) {
                                        if (move == king_coords) {
                                            string checkCoords;
                                            checkCoords = convert_to_LN(chessPieces[j][i]->getCoords()).first;
                                            checkCoords += ('0' + convert_to_LN(chessPieces[j][i]->getCoords()).second);
                                            check_coords.push(checkCoords);
                                            wcheck = true;
                                            counter++;
                                        }
                                        else if (counter == 0) {
                                            wcheck = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}

void ChessArray::check_bKing() {
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {

            if (chessPieces[b][a] != nullptr) {
                if (chessPieces[b][a]->getName() == "bKg") {
                    pair<int, int> king_coords = chessPieces[b][a]->getCoords();
                    int counter = 0;

                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            if (chessPieces[j][i] != nullptr && chessPieces[j][i]->getColor() != chessPieces[b][a]->getColor() && chessPieces[j][i]->getMoves(chessPieces).size() > 0) {
                                for (auto move : chessPieces[j][i]->getMoves(chessPieces)) {
                                    if (move == king_coords) {
                                        string checkCoords;
                                        checkCoords = convert_to_LN(chessPieces[j][i]->getCoords()).first;
                                        checkCoords += ('0' + convert_to_LN(chessPieces[j][i]->getCoords()).second);
                                        check_coords.push(checkCoords);
                                        bcheck = true;
                                        counter++;
                                    }
                                    else if (counter == 0) {
                                        bcheck = false;
                                    }       
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}

bool ChessArray::isValidMove(Piece* piece, pair<int, int> new_coords, char color) {
    int x = new_coords.first;
    int y = new_coords.second;
    int old_x = piece->getCoords().first;
    int old_y = piece->getCoords().second;
    
    Piece* temp;
    if (piece != nullptr) {
        temp = piece->clone();
    } else temp = nullptr;
    
    Piece* temp_overlayed;
    if (chessPieces[y][x] != nullptr) {
        temp_overlayed = chessPieces[y][x]->clone();
    } else temp_overlayed = nullptr;

    for (auto move : this->getPiece(old_x, old_y)->getMoves(ChessArray::chessPieces)) {
        if (new_coords == move) {
            this->getPiece(old_x, old_y)->movePiece(new_coords, ChessArray::chessPieces);
            break;
        }
    }

    if(color == 'w') check_wKing();
    else if (color == 'b') check_bKing();

    if (temp != nullptr) {
        chessPieces[old_y][old_x] = temp->clone();
    } else chessPieces[old_y][old_x] = nullptr;
    
    if (temp_overlayed != nullptr) {
        chessPieces[y][x] = temp_overlayed->clone();
    }
    else chessPieces[y][x] = nullptr;

    return !getKingCheck(color);
}

bool ChessArray::checkmate(char color) {
    if (!getKingCheck(color)) {
        return false;
    }
    cout << "made it here" << endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessPieces[j][i] != nullptr && chessPieces[j][i]->getColor() == color) {
                for (auto move : chessPieces[j][i]->getMoves(ChessArray::chessPieces)) {
                    cout << chessPieces[j][i]->getName() << endl;
                    if (isValidMove(chessPieces[j][i], move, color)) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

pair<char, int> ChessArray::convert_to_LN(pair<int, int> coords) {
    char x = 'A' + coords.first;
    int y = 8 - coords.second;

    return make_pair(x, y);
}

pair<int, int> ChessArray::convert_to_NN(pair<char, int> coords) {
    int x = coords.first - 'A';
    int y = 8 - coords.second;

    return make_pair(x, y);
}

void ChessArray::handlePawnPromotion(Piece* pawn, string piece_name) {
    char color = pawn->getColor();
    pair<int, int> coords = pawn->getCoords();
    int x = coords.first;
    int y = coords.second;

    if(pawn->getName().find("Pw")) {
        if(pawn->getColor()== 'w') {
            if (pawn->getCoords().second == 0) {
                chessPieces[y][x] = nullptr;;
                if(piece_name.find("Bishop") != string::npos) chessPieces[y][x] = new Bishop(color, coords);
                else if(piece_name.find("Rook") != string::npos) chessPieces[y][x] = new Rook(color, coords);
                else if(piece_name.find("Knight") != string::npos) chessPieces[y][x] = new Knight(color, coords);
                else if(piece_name.find("Queen") != string::npos) chessPieces[y][x] = new Queen(color, coords);
            }
        }
        else if(pawn->getColor()== 'b') {
            if (pawn->getCoords().second == 7) {
                chessPieces[y][x] = nullptr;;
                if(piece_name.find("Bishop") != string::npos) chessPieces[y][x] = new Bishop(color, coords);
                else if(piece_name.find("Rook") != string::npos) chessPieces[y][x] = new Rook(color, coords);
                else if(piece_name.find("Knight") != string::npos) chessPieces[y][x] = new Knight(color, coords);
                else if(piece_name.find("Queen") != string::npos) chessPieces[y][x] = new Queen(color, coords);
            }
        }
    }
}
