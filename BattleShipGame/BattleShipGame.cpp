// BattleShipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include <cstdlib> to create random inputs by the "ai".
//#include <ctime> to create truly random numbers with the <cstdlib> random functions.
//shoot() function recieves input from the player and inputs into the check_hit() function, and outputs whether or not the shot hit or missed.
//check_hit() function checks the board for whether or not the input was successful or not, and outputs the answer to the shoot() function.
//set_board() to initially set all values of the board to O.
//Displayboard() to show all of the player's board values to them.
//main() to start the thing.

//#include <cstdlib> to create random inputs by the "ai".
//#include <ctime> to create truly random numbers with the <cstdlib> random functions.
#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//shoot() function recieves input from the player and inputs into the check_hit() function, and outputs whether or not the shot hit or missed.
void shoot(char coordinatex, char coordinatey, char board[15][15]);

//check_hit() function checks the board for whether or not the input was successful or not, and outputs the answer to the shoot() function.
bool check_hit(int x, int y, char board[15][15]);

//set_board() to initially set all values of the board to O.
void set_board(char board[15][15]);

//Displayboard() to show all of the player's board values to them.
void DisplayBoard(char board[15][15]);

//life_test to check if any of a player's ships are alive. Usage will be in a while loop that will finish the game if one's ships have died. Undecided function name.
bool life_test(char board[15][15]);

//main() to start the thing.
int main()
{
	char bottom_board[15][15] = {};
	char top_board[15][15] = {};
	char ai_board[15][15] = {};

	set_board(top_board);
	set_board(bottom_board);
	set_board(ai_board);
	DisplayBoard(bottom_board);

	return 0;
}

void DisplayBoard(char board[15][15])
{
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			std::cout << board[x][y] << "\t";
		}
		std::cout << std::endl;
	}

}

void set_board(char board[15][15])
{
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++)
		{
			board[x][y] = 'O';
		}
	}
}
//For now, undecided variables for shoot() function. Suggesting variable usage of x1 and y1.
void shoot(char coordinatex, char coordinatey, char board[15][15])
{
	std::cout << "Where would you like to aim?\n";
	std::cin >> coordinatex;
	std::cin >> coordinatey;
	bool hit = check_hit(coordinatex, coordinatey, board);
	if (hit)
		board[coordinatex][coordinatey] = 'H';
	else
		board[coordinatex][coordinatey] = 'X';
}

bool check_hit(int x, int y, char board[15][15])
{
	if (board[x][y] = '#')
		return true;
	return false;
}

//Reiteration: function name "life_test" undecided. Also requesting possible shortening of code.
bool life_test(char board[15][15])
{
	int lifetest = 0;
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			if(board[x][y] = '#')
			lifetest++;
		}
	}
	if (lifetest >= 1)
		return true;
	return false;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
