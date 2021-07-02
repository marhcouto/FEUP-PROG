#pragma once
#include <vector>

class Pool {
public:
    std::vector <char> poolVector;  //Vector that represents the pool (class with no constructor because it was easier to
    friend class Board;            //the board constructor to build the vector)
};