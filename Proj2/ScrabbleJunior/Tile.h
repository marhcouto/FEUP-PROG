#pragma once

class Tile {                              //Class that represents a letter in a coordinate
public:                                 
    bool used = false;                    //True if the coordinates already have a tile
    bool firstLetterH = false;            //True if the coordinates represent the first letter available in a vertical word
    bool firstLetterV = false;            //True if the coordinates represent the first letter available in a horizontal word
    bool lastLetterV = false;             //True if the coordinates represent the last letter available in a vertical word
    bool lastLetterH = false;             //True if the coordinates represent the last letter available in a horizontal word
    char letter;                          //Letter in the board coordinates
    bool vertical = false;                //True if the coordinates represent a letter that belongs to a vertical word
    bool horizontal = false;              //True if the coordinates represent a letter that belongs to a horizontal word
};