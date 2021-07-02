#include <iostream>
#include <windows.h>

using namespace std;

void setcolor(unsigned int color) //Used to change the colours of the outputed board
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}
void tabuleiro(int (&b)[12], int P1, int P2) //Prints out the board on the console
{
	string str1, str2;                                               // Measures for when the values presented in the
	str1 = " P2  | ";                                               // board get bigger than 9 (have 2 digits)
	str2 = "| ";

	string b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1, b0;
	b11 = "( ";
	b10 = "( ";
	b9 = "( ";
	b8 = "( ";
	b7 = "( ";
	b6 = "( ";
	b5 = "( ";
	b4 = "( ";
	b3 = "( ";
	b2 = "( ";
	b1 = "( ";
	b0 = "( ";

	if (P2 >= 10)
		str1 = " P2  |";
	if (P1 >= 10)
		str2 = "|";

	if (*(b + 11) >= 10)
		b11 = "(";
	if (*(b + 10) >= 10)
		b10 = "(";
	if (*(b + 9) >= 10)
		b9 = "(";
	if (*(b + 8) >= 10)
		b8 = "(";
	if (*(b + 7) >= 10)
		b7 = "(";
	if (*(b + 6) >= 10)
		b6 = "(";
	if (*(b + 5) >= 10)
		b5 = "(";
	if (*(b + 4) >= 10)
		b4 = "(";
	if (*(b + 3) >= 10)
		b3 = "(";
	if (*(b + 2) >= 10)
		b2 = "(";
	if (*(b + 1) >= 10)
		b1 = "(";
	if (*(b + 0) >= 10)
		b0 = "(";
	
	cout << "                      --OWARE--\n";
	setcolor(2);
	cout << "\nPlayer2:    |h|  |g|  |f|  |d|  |s|  |a|" << endl;
	setcolor(15);
	cout << "      --   -----------------------------   --" << endl;
	setcolor(2);
	cout << "     |  | ";
	setcolor(15);
	cout << "|";
	setcolor(2);
	cout << b11 << *(b + 11) << ") " <<  b10 << *(b + 10) << ") " <<  b9 << *(b + 9) << ") "
		<< b8 << *(b + 8) << ") " <<  b7 << *(b + 7) << ") " <<  b6 << *(b + 6) << ")";
	setcolor(15);
	cout << "|";
	setcolor(4);
	cout << " |  |" << endl;
	setcolor(2);
	cout << str1 << P2 << "|";
	setcolor(15);
	cout << " |                             | ";
	setcolor(4);
	cout << str2 << P1 << "|  P1" << endl;
	setcolor(2);
	cout << "     |  | ";
	setcolor(15);
	cout << "|";
	setcolor(4);
	cout << b0 << *(b + 0) << ") " <<  b1 << *(b + 1) << ") " <<  b2 << *(b + 2) << ") "
		<< b3 << *(b + 3) << ") " <<  b4 << *(b + 4) << ") " <<  b5 << *(b + 5) << ")";
	setcolor(15);
	cout << "|";
	setcolor(4);
	cout << " |  |" << endl;
	setcolor(15);
	cout << "      --   -----------------------------   --" << endl;
	setcolor(4);
	cout << "Player1:    |a|  |s|  |d|  |f|  |g|  |h|\n" << endl;
	setcolor(15);
	
}
bool is_board_0(int (&b)[12], bool player) // Adopts true value if, after a play, the opponent's board is zeroed
{
	bool empty;
	int amount = 0;                                   // Amount of house with seeds
	if (player)                                       // Depending on the player, decides which side of the board to analyze
	{
		for (int i = 6; i <= 11; i++)
		{
			amount = amount + *(b + i);
		}
	}
	else
		for (int i = 0; i <= 5; i++)
		{
			amount = amount + *(b + i);
		}
	if (amount == 0)
		empty = true;
	else
		empty = false;
	return empty;
}
void is_capture(bool player, int (&b)[12], int pos, int &p1_score, int &p2_score) // Alters the players' score and the 
{                                                                                // board in case of a capture
	bool capture = true;

	while (capture)                                    // While there was a capture in the previous house analyzed, the cycle continues
	{                                                 // and it moves to analyze the previous house
		if (*(b + pos) == 2 or *(b + pos) == 3)
		{
			int gain = b[pos];                        // Amount to increment in the player's score
			if (player and pos >= 6)                  // Capture only counts in the opponents board
			{
				p1_score = p1_score + gain;
				*(b + pos) = 0;
				pos--;
			}
			else if (!player and pos <= 5)
			{
				p2_score = p2_score + gain;
				*(b + pos) = 0;
				pos--;
			}
			else
				capture = false;
		}
		else
			capture = false;	
	}
}
void move(int (&b)[12], int &pos) // Alters the board depending on the user's move
{
	int value = *(b + pos);
	int init_pos = pos;
	while (value > 0)
	{
		pos++;
		pos = pos % 12;                     // Keeping the position inside the board
		if (pos != init_pos)                // In case it had more than 11 seeds in the chosen house
		{
			*(b + pos) = *(b + pos) + 1;    // Leaving the seed
			value--;
		}
	}
	*(b + init_pos) = 0;                    // Leaving the chosen house seedless
}
void whose_turn(int t, bool &p1) // Verifies whose turn it is
{
	if (t % 2 == 1)              // If the turn is even, it's player 2's turn
		p1 = true;
	else
		p1 = false;
}
void input_setup(bool player, int &position, int(&b)[12]) // Defines the house where the seeds will be taken from
{
	string play;
	string str_player;

	if (player)                         
		str_player = "Player1";
	else
		str_player = "Player2";

	bool good_play = false;

	while (!good_play)                               // Only moves to the next task if the input is valid
	{
		cout << str_player << "'s turn:" << endl;
		cin >> play;

		if (play == "a")                             // Had previously used switch but strings were not allowed and character would
		{											// make the game malfunction if someone submitted two valid character in one play
			if (player)
				position = 0;
			else
				position = 6;
			good_play = true;
		}
		else if (play == "s")
		{
			if (player)
				position = 1;
			else
				position = 7;
			good_play = true;
		}
		else if (play == "d")
		{
			if (player)
				position = 2;
			else
				position = 8;
			good_play = true;
		}
		else if (play == "f")
		{
			if (player)
				position = 3;
			else
				position = 9;
			good_play = true;
		}
		else if (play == "g")
		{
			if (player)
				position = 4;
			else
				position = 10;
			good_play = true;
		}
		else if (play == "h")
		{
			if (player)
				position = 5;
			else
				position = 11;
			good_play = true;
		}
		else
			cout << "\nCharacter not valid\nPlease insert valid character\n\n";

		if (*(b + position) == 0)  // Can´t choose a seedless house
		{
			cout << "\nThis house has no seeds in it, choose another one\n\n";
			good_play = false;
		}
	}
}
void is_infinit(int b[], bool &infinity_case) // Verifies if the game has fallen into a specific infinite loop
{
	int last_pos = 0;
	int count = 0;
	bool inv_answer = true;

	for (int i = 0; i <= 11; i++)              // Verifies if there are only houses with less than 2 seeds and, if so, how many have 1
	{
		if (*(b + i) > 1)
		{
			infinity_case = false;
			break;
		}

		else if (*(b + i) == 1)
		{
			last_pos = i;
			count++;
		}
	}
	if (count <= 2 and infinity_case)  // If there are only 2 houses with seeds and both only with one, verifies if one is after the other or not
	{
		if (*(b + ((last_pos + 1) % 12)) == 0 and *(b + ((last_pos - 1) % 12)) == 0)
		{
			cout << "The game will have no end, would you like to continue?\nIf so, type 'yes', else, type 'no'\n"; // If the game has fallen into
			string answer;                                                                                    // an endless loop, asks the player
			while (inv_answer)																			// if he wants to continue
			{
				cin >> answer;
				if (answer == "no")                                // If not, the game is ended and the winner is the player with the highest score
				{
					infinity_case = true;
					inv_answer = false;
				}
				else if (answer == "yes")
				{
					infinity_case = false;
					inv_answer = false;
				}
				else
					cout << "Invalid answer, please, type a valid answer:\n";
			}
		}
		else
			infinity_case = false;
	}
}
void array_copy(int(&b)[12], int(&b_c)[12]) // Makes array b_c's elements equal to array b's, used to get back to a previous play in case 
{										   // the opponent's board has been zeroed
	for (int i = 0; i <= 11; i++)
	{
		*(b_c + i) = *(b + i);
	}
}
bool gameover(int p1_score, int p2_score, bool infinity_case) // Checks when the game is over
{
	if (p1_score > 24 or p2_score > 24 or (p1_score == 24 and p2_score == 24) or infinity_case)
		return true;
	else
		return false;
}
void winner(int p1_score, int p2_score) // Announces the winner 
{
	string str_p1 = "Player1 won the game!";
	string str_p2 = "Player2 won the game!";
	string draw = "It's a draw!";
	if (p1_score > p2_score)
		cout << str_p1 << endl;
	else if (p1_score < p2_score)
		cout << str_p2 << endl;
	else
		cout << draw << endl;
}
int main()
{
	bool player1;                                         // This boolean's valuee is true if it is player1's turn, otherwise it's vaçue false
	int position;                                         // The position is a variable used for various instances in the fase of executing the move and a possible capture
	int player1_score, player2_score;
	int turn = 1;	                                      // The turn the game is on is important to decide whose time is to play
	player1_score = 0;                                    // Player 1's score
	player2_score = 0;                                    // Player 2's score
	int board[12] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}; // Determines the number os seeds in each house
	bool infinity = false;                                // Used to determine the continuation of the game in case of an infinit loop


	while (!gameover(player1_score, player2_score, infinity))
	{
		int b_copy[12];
		int init_score1 = player1_score;  // Making copies of the players' scores
		int init_score2 = player2_score; // in case there is need to null the play
		array_copy(board, b_copy);        // Making a copy of the board in case there is need to null the play
		
		whose_turn(turn, player1);                                          // Deciding whose turn it is by altering the value of the boolean 'player1'
		tabuleiro(board, player1_score, player2_score);                     // Setting up the board in the console 
		input_setup(player1, position, board);                              // Deciding what the user's input means to the game
		move(board, position);                                              // Executing the changes on the board, depending on the player's 'move' (input)
		is_capture(player1, board, position, player1_score, player2_score); // Verifying if there has occured a capture
		is_infinit(board, infinity);                                        // Verifying if the game has not fallen into a infinite loop

		if (gameover(player1_score, player2_score, infinity))               // Making sure the game skips the rest of the cycle 
			continue;                                                      // in case of the game being over   
		 
		if (is_board_0(board, player1))                                     // Turning the play down in case the opponent's board gets zeroed
		{
			cout << "\nINVALID PLAY: opponent's board would be zeroed\n";
			array_copy(b_copy, board);
			player1_score = init_score1;
			player2_score = init_score2;
			continue;

		}
		turn++;
	}
	winner(player1_score, player2_score); // Announcing the winner
	
	return 0;
}