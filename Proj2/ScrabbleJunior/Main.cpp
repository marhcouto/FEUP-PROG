#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <map>
#include <iterator>
#include "Tile.h"
#include "Pool.h"
#include "Player.h"
#include "Board.h"

void Instructions(void) { //Prints instructions according to the user's decision

    bool stop = false;
    std::string response;

    std::cout << "Do you want to read the game's intructions/rules?('yes' or 'no')\n";

    do {
        std::cin >> response;
        if (response == "yes" || response == "no")
            stop = true;
        else
            std::cout << "Invalid answer. Please type 'yes' or 'no'\n";
    } while (!stop);

    if (response == "yes")
        std::cout << "\n Each player starts the game with 7 tiles. Each tile has a letter on it.\n"
        << "In each turn, the player must play 2 of its tiles on the board.\n"
        << "The tiles have to be played on coordinates that represent the first\n"
        << "available letter in a word. If a player does not have any tile that\n"
        << "fills the requirements on his 'deck', the game will automatically\n"
        << "draw tiles from the pool until the play is possible. Scoring chips\n"
        << "are earned every time the player places the last letter in a word.\n"
        << "Whoever has the most scoring chips when there are no tiles left wins.\n\n";

}
void ChangeColor(unsigned int color) {                    //Changes color    
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color);
}                               
void printColored(Board& board, char bigL, char smallL) { //Decides what to print in each coordinate, used in display
    unsigned int color = 8;
    if (board.boardMap.count({ bigL, smallL })) {
        if (board.boardMap[{bigL, smallL}].used)          //If the coordinate already has a tile
            color = 4;
        else if (board.boardMap[{bigL, smallL}].firstLetterH || board.boardMap[{bigL, smallL}].firstLetterV) //If it is a firts letter
            color = 10;
        ChangeColor(color);
        std::cout << board.boardMap[{bigL, smallL}].letter << " ";
        ChangeColor(8);
    }
    else
        std::cout << "  ";                               //If there's nothing in the coordinate
    ChangeColor(15);
}
void TileRequester(Player& player, Board& board, Pool& pool) {  //Requests tiles from the pool to the player's deck 
    unsigned int goodTiles = 0;                                //if he has no playable ones
    char letter;

    for (unsigned int i = 0; i < player.deck.size(); i++) {
        letter = player.deck[i];
        for (auto it = board.boardMap.begin(); it != board.boardMap.end(); it++) {
            if (letter == it->second.letter && (it->second.firstLetterH || it->second.firstLetterV))  //Checking if there are any available
                goodTiles++;                                                                         //tiles in the deck
        }
    }
    if (goodTiles == 0) {
        std::cout << "No matching tiles. Withdrawing a tile from the pool.\n";
        player.DrawFromPool(pool, 1);
        TileRequester(player, board, pool);
    }
}
void Display(Board& board, std::vector <Player> playersVector) {        //Prints the board and other info

    int hight = board.boardSize.first;           //Number of lines
    int length = board.boardSize.second;         //Number of columns
    char smallL = 'a';
    char bigL = 'A';

    system("CLS");

    std::cout << "             SCRABBLE\n\n";

    std::cout << "  ";
    while (length > 0) {
        std::cout << smallL << " ";
        smallL = char(int(smallL) + 1);
        length--;
    }
    std::cout << " | ";
    unsigned int nPlayers = playersVector.size();

    std::cout << "Scoring chips: | ";

    for (unsigned int i = 0; i < playersVector.size(); i++) {
        ChangeColor(5);
        std::cout << playersVector[i].GetName() << ": " << playersVector[i].GetScore();
        ChangeColor(15);
        std::cout << " | ";
    }
    std::cout << "\n";

    smallL = 'a';
    length = board.boardSize.second;

    while (hight > 0) {
        std::cout << bigL << " ";
        while (length > 0) {
            printColored(board, bigL, smallL);
            length--;                                       //Printing the board
            smallL++;
        }
        bigL++;
        smallL = 'a';
        length = board.boardSize.second;
        hight--;
        std::cout << " |";
        if (hight == 0) {
            ChangeColor(8);
            std::cout << " Grey - Normal tile |";
            ChangeColor(15);
        }
        if (hight == 1) {
            ChangeColor(9);
            std::cout << " Blue - Tile good to play from your pool |";              //Color scheme
            ChangeColor(15);
        }
        if (hight == 2) {
            ChangeColor(4);
            std::cout << " Red - A tile was already placed in those coordinates |";
            ChangeColor(15);
        }
        if (hight == 3) {
            ChangeColor(10);
            std::cout << " Green - Available spaces to play on the board |";
            ChangeColor(15);
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}
void PlayerMoveSetter(Player& player, Board& board) {  //Sets the player's move 

    std::string playerName = player.GetName();
    std::pair<char, char> coordPair;
    char tile1, coordinate1, coordinate2;

    std::string cinFailMsg = "Input type invalid.";
    std::string tileFailMsg = "There are no tiles that correspond with the choosen letter in your deck.";
    std::string coordFailMsg = "The coordinate you chose has no letters in the board.";
    std::string tileCoordFailMsg = "The letter you chose doesn't correspond to the posicion chosen in the board.";
    std::string notFirstLetterFailMsg = "The coordinates you chose to place your tile don't represent the first letter available of any word.";
    std::string usedLetterFailMsg = "The coordinates you chose to place your tile already have a tile placed.";

    bool tileFail;
    bool coordFail;
    bool tileCoordFail;
    bool stop;                                     //Different types of errors that could come up from input and its messages
    bool notFirstLetterFail;
    bool usedLetterFail;

    if(player.firstTile)
        std::cout << "Your turn " << playerName << std::endl;

    std::cout << "Your Pool: ";
    ChangeColor(8);

    for (unsigned int i = 0; i < player.deck.size(); i++) {
        for (auto it = board.boardMap.begin(); it != board.boardMap.end(); it++) {
            if (player.deck[i] == it->second.letter && (it->second.firstLetterH || it->second.firstLetterV))
                ChangeColor(9);
        }
        std::cout << "-" << player.deck[i] << " ";
        ChangeColor(8);
    }
    ChangeColor(15);

    std::cout << std::endl;


    do {
        if (player.firstTile)
            std::cout << "Choose one tile from your tile collection (must be capital letter).\n";
        else
            std::cout << "Choose another tile from your tile collection (must be capital letter).\n";
        std::cin >> tile1;
        std::cout << "\nChoose the coordinate corresponding to the line you want the tile placed on (must be capital letter).\n";
        std::cin >> coordinate1;
        std::cout << "\nChoose the coordinate corresponding to the column you want the tile placed on (must be small letter).\n";
        std::cin >> coordinate2;

        coordPair = { coordinate1, coordinate2 };

        tileFail = !std::count(player.deck.begin(), player.deck.end(), tile1);
        coordFail = (board.boardMap.count(coordPair) == 0);
        tileCoordFail = board.boardMap[{coordPair}].letter != tile1;
        notFirstLetterFail = !(board.boardMap[{coordPair}].firstLetterH || board.boardMap[{coordPair}].firstLetterV);
        usedLetterFail = board.boardMap[{coordPair}].used;

        if (std::cin.fail()) {
            std::cout << cinFailMsg << std::endl;
            stop = false;
        }
        else if (tileFail) {
            std::cout << tileFailMsg << std::endl;
            stop = false;
        }
        else if (coordFail) {
            std::cout << coordFailMsg << std::endl;
            stop = false;
        }
        else if (tileCoordFail) {
            std::cout << tileCoordFailMsg << std::endl;
            stop = false;
        }
        else if (notFirstLetterFail) {
            std::cout << notFirstLetterFailMsg << std::endl;
            stop = false;
        }
        else if (usedLetterFail) {
            std::cout << usedLetterFailMsg << std::endl;
            stop = false;
        }
        else
            stop = true;
    } while (!stop);

    std::vector <char> move = { coordinate1, coordinate2, tile1 };
    player.move = move;
}
void Play(Player& player, Board& board) {

    std::vector<char> move = player.move;
    std::vector<char> ::iterator iterOfUsedTile = std::find(player.deck.begin(), player.deck.end(), move[2]);
    player.deck.erase(iterOfUsedTile);

    board.boardMap[{move[0], move[1]}].used = true;

    if (board.boardMap[{move[0], move[1]}].horizontal) {
        if (board.boardMap[{move[0], move[1]}].lastLetterH)
            player.ScoreIncrementer();
        if (board.boardMap[{move[0], move[1]}].firstLetterH)
            board.boardMap[{move[0], char(int(move[1]) + 1)}].firstLetterH = true;
        board.boardMap[{move[0], move[1]}].firstLetterH = false;
    }

    if (board.boardMap[{move[0], move[1]}].vertical) {
        if (board.boardMap[{move[0], move[1]}].lastLetterV)
            player.ScoreIncrementer();
        if (board.boardMap[{move[0], move[1]}].firstLetterV)
            board.boardMap[{char(move[0] + 1), move[1]}].firstLetterV = true;
        board.boardMap[{move[0], move[1]}].firstLetterV = false;
    }
}
bool GameOver(Board& board) {
    unsigned int nonUsedTiles = 0;
    for (std::map < std::pair<char, char>, Tile > ::iterator it = board.boardMap.begin(); it != board.boardMap.end(); it++) {
        if (!(it->second.used))
            nonUsedTiles++;
    }
    if (nonUsedTiles == 0)
        return true;
    else
        return false;
}
void GameCloser(std::vector <Player> playersVector) {

    unsigned int highestScore = 0;
    std::vector <Player> winners;
    std::string multipleWinners;

    for (unsigned int i = 0; i < playersVector.size(); i++) {
        if (playersVector[i].GetScore() > highestScore) {
            highestScore = playersVector[i].GetScore();
        }
    }
    for (unsigned int i = 0; i < playersVector.size(); i++) {
        if (playersVector[i].GetScore() == highestScore)
            winners.push_back(playersVector[i]);
    }
    if (winners.size() == 1)
        std::cout << "The winner is " << winners[0].GetName() << " with " << winners[0].GetScore() << "scoring chips.\n";
    else {
        std::cout << "It's a draw between ";
        for (unsigned int i = 0; i < winners.size(); i++) {
            multipleWinners = multipleWinners + winners[i].GetName() + " with " + std::to_string(winners[i].GetScore()) + " scoring chips and ";
        }
        multipleWinners.erase(multipleWinners.end() - 4, multipleWinners.end());
        std::cout << multipleWinners;
    }
}
void AnotherGo (bool& playAgain) {
    std::string response;
    std::cout << "Want to play again?('yes' or 'no')\n";
    bool stop = false;

    do {
        std::cin >> response;
        if (response == "yes" || response == "no")
            stop = true;
        else
            std::cout << "Invalid answer. Please type 'yes' or 'no'\n";
    } while (stop);

    if (response == "yes")
        playAgain = true;
}                             
int MissingTiles(Player& player) {
    int missingTiles = 7 - player.GetDeck().size();
    if (missingTiles <= 0)
        return 0;
    else
        return missingTiles;
}
std::vector <Player> PlayersVectorCreator() {
    unsigned int nPlayers;
    std::cout << "The game supports 2-4 players, how many would like to play?\n";
    do {
        std::cin >> nPlayers;
        if (!(nPlayers >= 2 and nPlayers <= 4) || std::cin.fail()) {
            std::cout << "Invalid number of players, please type a integer between 2 and 4\n";
        }
    } while (!(nPlayers >= 2 and nPlayers <= 4) || std::cin.fail());


    Player player1("Player1");
    Player player2("Player2");

    std::vector <Player> pVector = { player1, player2 };

    if (nPlayers > 2) {
        Player player3("Player3");
        pVector.push_back(player3);
    }
    if (nPlayers > 3) {
        Player player4("Player4");
        pVector.push_back(player4);
    }
    return pVector;

}

void Game() {
    Instructions();  //Asks the user if he wants to read the basic instructions and, if so, prints them on the console

    Pool pool; 
    Board board(pool);

    std::vector <Player> playersVector = PlayersVectorCreator();  //Creating a vector with the players

    for (unsigned int i = 0; i < playersVector.size(); i++)
        playersVector[i].DrawFromPool(pool, 7);                   //Creating their deck/minipool

    while (!GameOver(board)) {                                    //Executes until there are no more tiles

        Display(board, playersVector);                            //Displays the gameboard, scores and a small color scheme
        TileRequester(playersVector[Player::turn], board, pool);  //Checks if the player has playable tiles and, if not, fetches tiles from the pool
        Player::firstTile = true;                                 //Used in PlayerMoveSetter
        PlayerMoveSetter(playersVector[Player::turn], board);     //Gets the player's move from the user
        Play(playersVector[Player::turn], board);                 //Executes the move
        Display(board, playersVector);                            //Repeating the process for the second tile to be played in a turn
        TileRequester(playersVector[Player::turn], board, pool);
        Player::firstTile = false;
        PlayerMoveSetter(playersVector[Player::turn], board);
        Play(playersVector[Player::turn], board);
        playersVector[Player::turn].DrawFromPool(pool, MissingTiles(playersVector[Player::turn])); //Draws tiles from the pool according to how many the player is missing
        Player::turn = (Player::turn + 1) % playersVector.size(); //Changes the turn
    }
    GameCloser(playersVector);                                    //Announces the winner
}

int main()
{
    bool playAgain;
    do {
        playAgain = false;
        Game();               //Actual game
        AnotherGo(playAgain); //Asks the user if it wants to play again and changes the playAgain's value accordingly
    } while (playAgain);




}