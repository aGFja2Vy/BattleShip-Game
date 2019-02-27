// BattleShipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
//Library includes random to create random inputs by the "ai".
#include <cstdlib>
//Libary included to create truly random numbers with the libary above random functions.
#include <ctime>

//DisplayBoard() to show all of the player's board values to them.
void DisplayBoard(char board[16][16]);

//set_board() to initially set all values of the board to O.
void set_board(char board[16][16]);

//ai_set_ship() to set the enemy's board via random input.
void ai_set_ship(char board[16][16], int ships);

//updateboard() to update the top board to the show the same as the ai board, but without the ships.
void updateboard(char board[16][16], char board2[16][16]);

//set_ship() to set up the player's ships with their inputs. Also resets int values so it may be used again.
void set_ship(char board[16][16], int ships, int x2 = 0, int y2 = 0);

//shoot() to recieve input from the player and input into the check_hit() function, and outputs whether or not the shot hit or missed.
void shoot(char board[16][16], int x1, int y1);

//ai_shoot() to generate random numbers and input it into a check_hit() function, and outputs whether or not the shot hit or missed.
void ai_shoot(char board[16][16], int &orientation, int xai, int yai);

//check_hit() to check the board for whether or not the input was successful or not, and outputs the answer to the shoot() function.
bool check_hit(int x, int y, char board[16][16], bool &duplicateShot);

bool check_hit(int x, int y, char board[16][16], bool &duplicateShot, bool &not_on_board);

//life_test() to check if any of a player's ships are alive. Will end the game if no ship spaces are found on either board.
bool life_test(char board[16][16]);

//hspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for horizontal orientation.
bool hspace_test(char board[16][16], int ships, int x2, int y2);

//vspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for vertical orientation.
bool vspace_test(char board[16][16], int ships, int x2, int y2);

//main() to start the thing.
int main()
{
	srand((unsigned)time(0));
	int xai = 0;
	int yai = 0;
	int orientation = 0;
	int turn_counter = 1;
	int ships[5] = { 5, 4, 4, 3, 2 };
	char bottom_board[16][16] = {};
	char top_board[16][16] = {};
	char ai_board[16][16] = {};

	set_board(top_board);
	set_board(bottom_board);
	set_board(ai_board);

	DisplayBoard(bottom_board);
	for (int w = 0; w < 5; w++) {
		set_ship(bottom_board, ships[w]);
		DisplayBoard(bottom_board);
		ai_set_ship(ai_board, ships[w]);
	}
	bool lifetest = life_test(bottom_board);
	bool ailifetest = life_test(ai_board);

	//Reminder to change the while loop to something more efficient
	//This maybe a good while loop :)
	while (lifetest && ailifetest) {
		shoot(ai_board, 0, 0);
		updateboard(ai_board, top_board);
		DisplayBoard(top_board);
		ailifetest = life_test(ai_board);
		if (!(ailifetest)) {
			std::cout << "You win!" << std::endl;
			DisplayBoard(ai_board);
			std::cout << "Turns taken: " << turn_counter << std::endl;
			return 0;
		}
		ai_shoot(bottom_board, orientation, xai, yai);
		DisplayBoard(bottom_board);
		lifetest = life_test(bottom_board);
		if (!(lifetest)) {
			std::cout << "You lost!" << std::endl;
			DisplayBoard(ai_board);
			std::cout << "Turns taken: " << turn_counter << std::endl;
			return 0;
		}
		turn_counter++;
	}
}

void DisplayBoard(char board[16][16])
{
	std::cout << "  |1  2  3  4  5  6  7  8  9  10 11 12 13 14 15" << std::endl;
	std::cout << "--|--------------------------------------------" << std::endl;
	for (int x = 0; x < 9; x++)
	{
		std::cout << x + 1 << " |";
		for (int y = 0; y < 15; y++)
		{
			std::cout << board[x][y] << "  ";
		}
		std::cout << std::endl;
	}
	for (int x = 9; x < 15; x++)
	{
		std::cout << x + 1 << "|";
		for (int y = 0; y < 15; y++)
		{
			std::cout << board[x][y] << "  ";
		}
		std::cout << std::endl;
	}
}

void set_board(char board[16][16])
{
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++)
		{
			board[x][y] = ' ';
		}
	}
}

void ai_set_ship(char board[16][16], int ships)
{
	bool ship_settle = false;
	do {
		bool spacetest = false;
		int x2 = std::rand() % 15;
		int y2 = std::rand() % 15;
		int position = std::rand() % 2;
		if (position == 0) {
			spacetest = hspace_test(board, ships, x2, y2);
			if (spacetest) {
				for (int y = 0; y < ships; y++) {
					board[x2][y2 - (ships / 2) - 1 + y] = '#';
				}
				ship_settle = false;
			}
		}
		else {
			spacetest = vspace_test(board, ships, x2, y2);
			if (spacetest) {
				for (int x = 0; x < ships; x++) {
					board[x2 - (ships / 2) - 1 + x][y2] = '#';
				}
				ship_settle = false;
			}
		}
		if (!(spacetest)) {
			ship_settle = true;
		}
	} while (ship_settle);
}

void updateboard(char board[16][16], char board2[16][16])
{
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			if (board[x][y] == 'H') {
				board2[x][y] = 'H';
			}
			else if (board[x][y] == 'X') {
				board2[x][y] = 'X';
			}
			else {
				board2[x][y] = ' ';
			}
		}
	}
}

//Figure out a way to set position to a bool value instead of a number?
void set_ship(char board[16][16], int ships, int x2, int y2)
{
	bool ship_settle = false;
	do {
		bool spacetest = false;
		int position = 0;
		std::cout << "Where would you like to place your ship?" << std::endl;
		std::cin >> x2 >> y2;
		std::cout << "1: Horizontal \n2: Vertical" << std::endl;
		std::cin >> position;
		if (position == 1) {
			spacetest = hspace_test(board, ships, x2, y2);
			if (spacetest) {
				for (int y = 0; y < ships; y++) {
					board[x2 - 1][y2 - (ships / 2) - 1 + y] = '#';
				}
				ship_settle = false;
			}
		}
		else {
			spacetest = vspace_test(board, ships, x2, y2);
			if (spacetest) {
				for (int x = 0; x < ships; x++) {
					board[x2 - (ships / 2) - 1 + x][y2 - 1] = '#';
				}
				ship_settle = false;
			}
		}
		if (!(spacetest)) {
			std::cout << "Invalid position." << std::endl;
			ship_settle = true;
		}
	} while (ship_settle);
}

void shoot(char board[16][16], int x1, int y1)
{
	bool hit = false;
	bool duplicateShot = false;
	bool not_on_board = false;

	do {
		std::cout << "Where would you like to aim?" << std::endl;
		std::cin >> x1 >> y1;
		//std::cin >> y1;
		hit = check_hit(x1 - 1, y1 - 1, board, duplicateShot, not_on_board);

		if (duplicateShot)
			std::cout << "Already shot there. Please try again." << std::endl;
		if (not_on_board)
			std::cout << "Inputs are not on the board. Please try again." << std::endl;

	} while (duplicateShot || not_on_board);

	if (hit) {
		board[x1 - 1][y1 - 1] = 'H';
		std::cout << "Hit!" << std::endl;
	}
	else {
		board[x1 - 1][y1 - 1] = 'X';
		std::cout << "Miss!" << std::endl;
	}
}
//Undecided variable names.
void ai_shoot(char board[16][16], int &orientation, int xai, int yai)
{
	bool duplicateShot = false;
	bool hit = false;
	bool not_on_board = false;
	//Really Dude
	//do {
	switch (orientation) {
	case 1: {
		std::cout << "\n Case: 1" << std::endl;
		//The xai + 1 thing wont work because it is not saving the last location it is coming from a new spot
		hit = check_hit(xai + 1, yai, board, duplicateShot, not_on_board);
		if (duplicateShot || not_on_board) {
			orientation--;
			break;
		}
		if (hit) {
			board[xai + 1][yai] = 'H';
			std::cout << "You've been hit!" << std::endl;
			xai++;
		}
		else {
			board[xai + 1][yai] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
		break;
	}
	case 2: {
		std::cout << "\n Case: 2" << std::endl;
		hit = check_hit(xai, yai + 1, board, duplicateShot, not_on_board);
		if (duplicateShot || not_on_board) {
			orientation--;
			break;
		}
		if (hit) {
			board[xai][yai + 1] = 'H';
			std::cout << "You've been hit!" << std::endl;
			yai++;
		}
		else {
			board[xai][yai + 1] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
		break;
	}
	case 3: {
		std::cout << "\n Case: 3" << std::endl;
		hit = check_hit(xai - 1, yai, board, duplicateShot, not_on_board);
		if (duplicateShot || not_on_board) {
			orientation--;
			break;
		}
		if (hit) {
			board[xai - 1][yai] = 'H';
			std::cout << "You've been hit!" << std::endl;
			xai--;
		}
		else {
			board[xai - 1][yai] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
		break;
	}
	case 4: {
		std::cout << "\n Case: 4" << std::endl;
		hit = check_hit(xai, yai - 1, board, duplicateShot, not_on_board);
		if (duplicateShot || not_on_board) {
			orientation--;
			break;
		}
		if (hit) {
			board[xai][yai - 1] = 'H';
			std::cout << "You've been hit!" << std::endl;
			yai--;
		}
		else {
			board[xai][yai - 1] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
		break;
	}
	default: {
		std::cout <<"\n Default"<< std::endl;
		//do {
		int xai = std::rand() % 15;
		int yai = std::rand() % 15;
		hit = check_hit(xai, yai, board, duplicateShot);
		//This is what happend to the last traitor
		//haha
	//} while (duplicateShot);
		if (hit) {
			board[xai][yai] = 'H';
			std::cout << "You've been hit!" << std::endl;
			orientation = 4;
		}
		else {
			board[xai][yai] = 'X';
			std::cout << "Enemy missed!" << std::endl;
		}
		break;
	}
	}
	//} while (duplicateShot);
}

bool check_hit(int x, int y, char board[16][16], bool &duplicateShot, bool &not_on_board)
{
	if ((x > 15) || (y > 15)) 
		not_on_board = true;
	else
		not_on_board = false;
	if ((board[x][y] == 'H') || (board[x][y] == 'X')) 
		duplicateShot = true;
	else
		duplicateShot = false;

	if (board[x][y] == '#')
		return true;
	return false;
}
bool check_hit(int x, int y, char board[16][16], bool &duplicateShot)
{
	if ((board[x][y] == 'H') || (board[x][y] == 'X'))
		duplicateShot = true;
	if (board[x][y] == '#')
		return true;
	return false;
}

//function name "life_test" undecided.
bool life_test(char board[16][16])
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

bool hspace_test(char board[16][16], int ships, int x2, int y2)
{
	int hspacetest = 0;
	for (int y = 0; y < ships; y++) {
		if (board[x2 - 1][y2 - (ships / 2) - 1 + y] == ' ') {
			hspacetest++;
		}
	}
	if (hspacetest == ships)
		return true;
	return false;
}
bool vspace_test(char board[16][16], int ships, int x2, int y2)
{
	int vspacetest = 0;
	for (int x = 0; x < ships; x++) {
		if (board[x2 - (ships / 2) - 1 + x][y2 - 1] == ' ') {
			vspacetest++;
		}
	}
	if (vspacetest == ships)
		return true;
	return false;
}
