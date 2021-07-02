
#include "board.h"

//All the comments are in the header file board.h

board::board(){
    cout << "Number of rows:\n";
    cin >> rows;
    while(cin.fail() || rows > 20){
        system("CLS");
        cout << "Number of rows:\n";
        cerr << "\nINVALID INPUT\n";
        cout << "Try again:\n";
        cin.clear();
        cin.ignore(132,'\n');
        cin >> rows;
    }
    cout << "\nNumber of collumns:\n";
    cin >> collumns;
    while(cin.fail() || collumns > 20){
        system("CLS");
        cout << "Number of collumns:\n";
        cerr << "\nINVALID INPUT\n";
        cout << "Try again:\n";
        cin.clear();
        cin.ignore(132,'\n');
        cin >> collumns;
    }
    cout << "How many words do you want to put on the board?\n";
    cin >> NumberOfWords;
    while(cin.fail() || rows > 20){
        system("CLS");
        cout << "How many words do you want to put on the board?\n";
        cerr << "\nINVALID INPUT\n";
        cout << "Try again:\n";
        cin.clear();
        cin.ignore(132,'\n');
        cin >> rows;
    }   
}

void board::display(){
    system("CLS");
    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(h,1 | FOREGROUND_INTENSITY);
    string index ;
    //division
    cout << "     ";
    for (int i=0; i<collumns;i++){
        cout << "--- ";
    }

    //first rows with all the collumn
    cout << "\n    | ";
    for (int i=0; i<collumns;i++){
        char a = i+97;
        SetConsoleTextAttribute(h,2 | FOREGROUND_INTENSITY);
        cout << a ;
        SetConsoleTextAttribute(h,1 | FOREGROUND_INTENSITY);
        cout << " | ";
    }

    //division
    cout << "\n --- ";
    for (int i=0; i<collumns;i++){
        cout << "--- ";
    }

    //rows
    for (int j=0;j<rows;j++){
        char b = j+65;
        cout << "\n| " ;
        SetConsoleTextAttribute(h,2 | FOREGROUND_INTENSITY);
        cout << b ;
        SetConsoleTextAttribute(h,1 | FOREGROUND_INTENSITY);
        cout << " | ";
        for (int i=0; i<collumns;i++){ // collumns
            index = "";
            char a = i+97;
            index += a;
            index += b;
            SetConsoleTextAttribute(h,15 | FOREGROUND_INTENSITY);
            if (boardmap.count(index)){
                cout << boardmap[index];
            }
            else{
                cout << " ";
            }
            SetConsoleTextAttribute(h,1 | FOREGROUND_INTENSITY);
            cout<< " | ";
        }
        cout << "\n --- ";
        for (int i=0; i<collumns;i++){
            cout << "--- ";
        }
    }
    cout << endl;
}

void board::SetWords(){
    ofstream outfile("board.txt");
    outfile << rows << " x " << collumns << endl;
    string word,index,tagain;
    char ori,x,y;
    for (int i=0;i<NumberOfWords;i++){
        display();
        cout << "Enter the word ("<< i+1 << "/" << NumberOfWords << ")"<< endl;
        // word.size() >1
        cin >> word;
        while (cin.fail() || !(word.size()>1)){
            cout << "\nINVALID OUTPUT\n" ;
            cout << "Try again\n";
            cin.clear();
            cin.ignore(132,'\n');
            cin >> word;
        }

        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if(!(IsInDic(word,"WORDS.TXT"))){
            cout << "\nThe word is not in the dictionary\n";
            cout << "Type anything to try again\n";
            cin.clear();
            cin.ignore(132,'\n');
            cin >> tagain;
            cin.clear();
            cin.ignore(132,'\n');
            i-= 1;
            continue;
        }
        display();
        cout << "Word: " << word;
        cout << "\nEnter de coordinates of the beginning of the word (ex. (aA) )\n";
        cin >> index;
        // index[0] must be in uppercase e index[1] must be in lowercase
        if (cin.fail() || !(index.size()==2) || !((index[0] - 'a') < 20 && (index[0] - 'a') >= 0) || !((index[1] - 'A')< 20 && (index[1] - 'A') >= 0)){
            cout << "INVALID INPUT\n";
            cout << "Type anything to try again\n";
            cin.clear();
            cin.ignore(132,'\n');
            cin >> tagain;
            cin.clear();
            cin.ignore(132,'\n');
            i-= 1;
            continue;
        }

        x = index[0];
        y = index[1];

        display();
        cout << "Word: " << word;
        cout << "\nCoordenate: " << index;
        cout << "\nEnter the orientation of the word(H/V)\n";
        cin >> ori;
        // must be H or V
        putchar(toupper(ori));
        if (cin.fail() || !(ori== 'H' || ori == 'V')){
           cout << "INVALID INPUT\n";
            cout << "Type anything to try again\n";
            cin.clear();
            cin.ignore(132,'\n');
            cin >> tagain;
            cin.clear();
            cin.ignore(132,'\n');
            i-= 1;
            continue; 
        }

        if (!(FitInBoard(rows,collumns,word,ori,x,y))){
            cout << "The word does not fit in the board\n";
            cout << "Type anything to try again\n";
            cin.clear();
            cin.ignore(132,'\n');
            cin >> tagain;
            cin.clear();
            cin.ignore(132,'\n');
            i-= 1;
            continue; 
        }
        else if ((!(intersect(boardmap,word,x,y,ori))) && i != 0){
            cout << "The word must intersect one of the others words in the board\n";
            cout << "Type anything to try again\n";
            cin.clear();
            cin.ignore(132,'\n');
            cin >> tagain;
            cin.clear();
            cin.ignore(132,'\n');
            i-= 1;
            continue; 
        }
        else if (intersect(boardmap,word,x,y,ori) == 2){
            cout << "The word does not intersect correctly\n";
            cout << "Type anything to try again\n";
            cin.clear();
            cin.ignore(132,'\n');
            cin >> tagain;
            cin.clear();
            cin.ignore(132,'\n');
            i-= 1;
            continue; 
        }

        outfile << index[1] << index[0] << " " << ori << " " << word << endl;
        
        SetWordsInMap(word,ori,x,y);

    }
    outfile.close();
}

void board::SetWordsInMap(string word,char ori,char x,char y){
    string index;
    char x1,y1;
    for (int i=0;i<word.size();i++){
        index = "";
        if (ori == 'H'){
            x1 = x + i;
            y1 = y;
        }
        else {
            y1 = y + i;
            x1 = x;
        }
        index += x1;
        index += y1;
        boardmap[index] = word[i];
    }
}

int IsInDic(string word,string words){
    int flag = 0;
    ifstream file;
    file.open(words);
    int i = 0;
    while(true){
        string x;
        file >> x;
        if (x == word){
            flag = 1;
            break;
        }
        if(file.eof()) break;
    }
    file.close();
    return flag;
}

int FitInBoard(int row,int collumn,string word,char ori,char x,char y){
    int x1 = x- 'a';
    int y1 = y - 'A';
    if ((ori == 'H') && (x1+word.length()>collumn)){
        return 0;
    }
    else if ((ori == 'V') && (y1+word.length()>row))
        return 0;
    else{
        return 1;
    }
}

int intersect(map<string,char> boardmap,string word,char x, char y, char ori){
    string index;
    char x1,y1;
    int flag = 0;
    for (int i=0;i<word.size();i++){
        index = "";
        if (ori == 'H'){
            x1 = x + i;
            y1 = y;
        }
        else {
            y1 = y + i;
            x1 = x;
        }
        index += x1;
        index += y1;
        
        if (boardmap.count(index)){       
            if (boardmap[index] == word[i]){
                flag = 1;
            }
            else {
                flag = 2;
                break;
            }
        }
    }
    return flag;
}

