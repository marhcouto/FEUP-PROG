#pragma once
#include <map>
#include <string>
#include "Pool.h"
#include "Tile.h"
#include "Player.h"


class Board {
    std::string fileName;
public:
    std::pair <int, int> boardSize;                                       //Dimensions
    std::map < std::pair < char, char>, Tile > boardMap;                  //Map that represents the board
    Board(Pool& pool);
};
