#include <iostream>
#include "board.h"

//All the comments are in the header filer board.h

int main(){
    string trash;
    board game1;
    game1.SetWords();
    game1.display();
    cout << "\nTHE BOARD WAS SUCCESSFULLY CREATED\n"<< "Type anything to leave...\n";
    cin >> trash;
    
    return 0;
}