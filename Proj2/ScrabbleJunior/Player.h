#pragma once
#include <vector>
#include <string>
#include "Pool.h"
#include "Board.h"

class Player {
    unsigned int score;       
    std::vector <char> move;  //Player's move (tile and coordinates)
    std::string name;        
    std::vector <char> deck;  //Player's mini pool
public:
    static bool firstTile;       //Used to decide output options (firsttile the player is placing on the turn or last)
    static unsigned int turn;    

    friend void PlayerMoveSetter(Player& player, Board& board);
    friend void Play(Player& player, Board& board);
    friend void TileRequester(Player& player, Board& board, Pool& pool);

    Player(std::string playerName);

    std::string GetName(void) const { return name; }
    int GetScore(void) const { return score; }
    std::vector <char> GetDeck(void) const { return deck; }

    void ScoreIncrementer(void) { score++; }  
    void DrawFromPool(Pool& pool, const unsigned int n);  //Used to give the player n tiles taken randomly from the pool

};

