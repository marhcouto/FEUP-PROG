#include "Board.h"
#include <fstream>
#include <iostream>
#include <sstream>

Board::Board(Pool& pool) {

    std::cout << "Which board file should be used?" << std::endl;
    std::ifstream boardStream;

    do {
        std::cin >> fileName;
        boardStream.open(fileName);
        if (boardStream.fail()) {
            std::cerr << "Input file opening failed.\n";                //Opening the file
            std::cout << "Try again\n";
        }
    } while (!boardStream.is_open());

    std::string dim;
    boardStream >> dim;
    int n = std::stoi(dim);           //Getting the board dimensions
    boardSize.first = n;
    boardStream.seekg(4);
    boardStream >> dim;
    n = std::stoi(dim);
    boardSize.second = n;

    char L, l, direc;
    std::string word;


    while (!boardStream.eof()) {
        boardStream >> L >> l >> direc >> word;
        for (unsigned int i = 0; i < word.size(); i++) {      //Building the boardMap
            boardMap[{L, l}].letter = word[i];
            pool.poolVector.push_back(word[i]);

            if (direc == 'H') {
                if (i == 0) {
                    boardMap[{L, l}].firstLetterH = true;
                }
                else if (i == word.size() - 1) {
                    boardMap[{L, l}].lastLetterH = true;
                }
                boardMap[{L, l}].horizontal = true;
                l = char(l + 1);
            }
            else {
                if (i == 0) {
                    boardMap[{L, l}].firstLetterV = true;
                }
                else if (i == word.size() - 1) {
                    boardMap[{L, l}].lastLetterV = true;
                }
                boardMap[{L, l}].vertical = true;
                L = char(L + 1);
            }
        }
    }
    boardStream.close();
}