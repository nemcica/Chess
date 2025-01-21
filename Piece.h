#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Piece {
protected:
    string name;
    pair<int, int> coords;
    char color;

public:

    Piece() { name = " "; coords = make_pair(9, 9); color = ' '; }
    Piece(string name, char color, pair<int, int> coords) : name(color + name), coords(coords), color(color) { }

    virtual Piece* clone() const { return new Piece(); }
   
    //Setters
    
    //Getters
    virtual vector<pair<int, int>> getMoves(vector<vector<Piece*>>& checker) { vector<pair<int, int>> moves; return moves; }
    void movePiece(pair<int, int> new_coords, vector<vector<Piece*>>& checker) { 
        if (checker[new_coords.second][new_coords.first] != nullptr) checker[new_coords.second][new_coords.first] = nullptr;
        checker[new_coords.second][new_coords.first] = this; 
        checker[coords.second][coords.first] = nullptr;
        this->coords = new_coords;
    }
    string getName() { return name; }
    char getColor() { return color; }
    pair<int, int> getCoords() { return coords; }


    virtual ~Piece() {}


};

