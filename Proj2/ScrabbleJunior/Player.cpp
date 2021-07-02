#include "Player.h"
#include <time.h>

unsigned int Player::turn = 0;         
bool Player::firstTile = true;          

Player::Player(std::string playerName) {
    name = playerName;
    score = 0;
}
void Player::DrawFromPool(Pool& pool, const unsigned int n) {      
    unsigned int randNumber;

    srand(time(NULL));
    if (n > 0) {
        for (unsigned int i = 0; i < n; i++) {
            randNumber = rand() % pool.poolVector.size();
            deck.push_back(pool.poolVector[randNumber]);
            pool.poolVector.erase(pool.poolVector.begin() + randNumber);
        }
    }

};
