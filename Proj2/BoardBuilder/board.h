#ifndef board_h
#define board_h
#include <map>
#include <string>
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <map>
#include <vector>
#include<bits/stdc++.h>
using namespace std;


class board{
    public:
        board();
        void display();// displays the current board on the screen
        void SetWords(); // sets the words on the board and creates the file board.txt
        void SetWordsInMap(string word,char ori,char x,char y); // sets the words in the map(boardmap)
    private:
        int NumberOfWords;
        int rows;
        int collumns;
        map<string,char> boardmap;
};

//check if the word intersects with any word in the board and if it intersects in a good place(return=1) or not(return=2)
int intersect(map<string,char> boardmap,string word,char x, char y, char ori);

//check if the world fits in the board
int FitInBoard(int row,int collumn,string word,char ori,char x,char y);

//check if the world is in the dictionary
int IsInDic(string word,string words);

#endif