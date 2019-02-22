// BattleShipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <ctime>

void shoot(char coordinatex, char coordinatey, char board[15][15]);
bool check_hit(int x, int y, char board[15][15]);
void set_board(char board[15][15]);
void DisplayBoard(char board[15][15]);

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

void set_board(char board[15][15])
{
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++)
		{
			board[x][y] = 'O';
		}
	}
}

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
