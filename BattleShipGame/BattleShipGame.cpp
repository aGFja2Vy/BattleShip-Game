// BattleShipGame.cpp : This file contains the 'main' function. Program e// BattleShipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include <cstdlib> to create random inputs by the "ai".
//#include <ctime> to create truly random numbers with the <cstdlib> random functions.
//DisplayBoard() to show all of the player's board values to them.
//set_board() to initially set all values of the board to O.
//set_ship() to set up the player's ships with their inputs. Also resets int values so it may be used again.
//shoot() to recieve input from the player and input into the check_hit() function, and outputs whether or not the shot hit or missed.
//check_hit() to check the board for whether or not the input was successful or not, and outputs the answer to the shoot() function.
//life_test() to check if any of a player's ships are alive. Will end the game if no ship spaces are found on either board.
//hspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for horizontal orientation.
//vspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for vertical orientation.
//main() to start the thing.

//#include <cstdlib> to create random inputs by the "ai".
//#include <ctime> to create truly random numbers with the <cstdlib> random functions.
#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//DisplayBoard() to show all of the player's board values to them.
void DisplayBoard(char board[15][15]);

//set_board() to initially set all values of the board to O.
void set_board(char board[15][15]);

//set_ship() to set up the player's ships with their inputs. Also resets int values so it may be used again.
void set_ship(char board[15][15], int x2 = 0, int y2 = 0);

//shoot() to recieve input from the player and input into the check_hit() function, and outputs whether or not the shot hit or missed.
void shoot(char coordinatex, char coordinatey, char board[15][15]);

//check_hit() to check the board for whether or not the input was successful or not, and outputs the answer to the shoot() function.
bool check_hit(int x, int y, char board[15][15]);

//life_test() to check if any of a player's ships are alive. Will end the game if no ship spaces are found on either board.
bool life_test(char board[15][15]);

//hspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for horizontal orientation.
bool hspace_test(char board[15][15], int x2, int y2);

//vspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for vertical orientation.
bool vspace_test(char board[15][15], int x2, int y2);

//main() to start the thing.
int main()
{
	int ships[5] = { 5, 4, 4, 3, 2 };
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
	std::cout << "   |1   2   3   4   5   6   7   8   9   10  11  12  13  14  15" << std::endl;
	std::cout << "---|----------------------------------------------------------" << std::endl;
	for (int x = 0; x < 15; x++)
	{
		std::cout << "   |";
		for (int y = 0; y < 15; y++)
		{
			std::cout << board[x][y] << "   ";
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

//Unfortunately, string variables don't seem to work with std::cin. For now, setting a number for horizontal or vertical position.
void set_ship(char board[15][15], int x2, int y2)
{
	bool ship_settle = false;
	do {
		bool hspacetest;
		bool vspacetest;
		x2 = 0;
		y2 = 0;
		int position = 0;
		std::cout << "Where would you like to place your ship?" << std::endl;
		std::cin >> x2 >> y2;
		std::cout << "1: Horizontal \n2: Vertical" << std::endl;
		std::cin >> position;
		if (position == 1) {
			hspacetest = hspace_test(board, x2, y2);
			if (hspacetest) {
				for (int y = 0; y < 5; y++) {
					board[x2][y2 - 2 + y] = '#';
				}
				ship_settle = false;
			}
		}
		else {
			vspacetest = vspace_test(board, x2, y2);
			if (vspacetest) {
				for (int x = 0; x < 5; x++) {
					board[x2 - 2 + x][y2] = '#';
				}
				ship_settle = false;
			}
		}
		if (!(hspacetest) || !(vspacetest)) {
			std::cout << "Invalid position.";
			ship_settle = true;
		}
	} while (ship_settle);
}

//For now, undecided variables for shoot() function. Suggesting variable usage of x1 and y1.
void shoot(char x1, char y1, char board[15][15])
{
	std::cout << "Where would you like to aim?\n";
	std::cin >> x1 >> y1;
	bool hit = check_hit(x1, y1, board);
	if (hit)
		board[x1][y1] = 'H';
	else
		board[x1][y1] = 'X';
}

bool check_hit(int x, int y, char board[15][15])
{
	if (board[x][y] == '#')
		return true;
	return false;
}

//function name "life_test" undecided. Also requesting possible shortening of code.
bool life_test(char board[15][15])
{
	int lifetest = 0;
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			if (board[x][y] == '#')
				lifetest++;
		}
	}
	if (lifetest >= 1)
		return true;
	return false;
}

//So far, the space tests will only be able to detect space for a 5-space ship. We will need to change this in the future to work with smaller ships.
bool hspace_test(char board[15][15], int x2, int y2)
{
	int hspacetest = 0;
	for (int y = 0; y < 5; y++) {
		if (board[x2][y2 - 2 + y] == 'O') {
			hspacetest++;
		}
	}
	if (hspacetest == 5)
		return true;
	return false;
}
bool vspace_test(char board[15][15], int x2, int y2)
{
	int vspacetest = 0;
	for (int x = 0; x < 5; x++) {
		if (board[x2 - 2 + x][y2] == 'O') {
			vspacetest++;
		}
	}
	if (vspacetest == 5)
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

