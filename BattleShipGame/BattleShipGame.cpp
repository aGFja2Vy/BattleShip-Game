// BattleShipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include <cstdlib> to create random inputs by the "ai".
//#include <ctime> to create truly random numbers with the <cstdlib> random functions.
//DisplayBoard() to show all of the player's board values to them.
//set_board() to initially set all values of the board to O.
//ai_set_ship() to set the enemy's board via random input.
//updateboard() to update the top board to the show the same as the ai board, but without the ships.
//set_ship() to set up the player's ships with their inputs. Also resets int values so it may be used again.
//shoot() to recieve input from the player and input into the check_hit() function, and outputs whether or not the shot hit or missed.
//ai_shoot() to generate random numbers and input it into a check_hit() function, and outputs whether or not the shot hit or missed.
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
void ai_shoot(char board[16][16], int orientation, int xai, int yai);

//check_hit() to check the board for whether or not the input was successful or not, and outputs the answer to the shoot() function.
bool check_hit(int x, int y, char board[16][16]);

//life_test() to check if any of a player's ships are alive. Will end the game if no ship spaces are found on either board.
bool life_test(char board[16][16]);

//hspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for horizontal orientation.
bool hspace_test(char board[16][16], int ships, int x2, int y2);

//vspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for vertical orientation.
bool vspace_test(char board[16][16], int ships, int x2, int y2);

//main() to start the thing.
int main()
{
	srand((unsigned int)time(0));
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

	//Reminder to change the while loop to something more efficient.
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
	std::cout << "   |1  2  3  4  5  6  7  8  9  10 11 12 13 14 15" << std::endl;
	std::cout << "---|--------------------------------------------" << std::endl;
	for (int x = 0; x < 9; x++)
	{
		std::cout << x + 1 << "  |";
		for (int y = 0; y < 15; y++)
		{
			std::cout << board[x][y] << "  ";
		}
		std::cout << std::endl;
	}
	for(int x = 9; x < 15; x++) 
	{
		std::cout << x + 1 << " |";
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
					board[x2][y2 - (ships / 2) + y] = '#';
				}
				ship_settle = false;
			}
		}
		else {
			spacetest = vspace_test(board, ships, x2, y2);
			if (spacetest) {
				for (int x = 0; x < ships; x++) {
					board[x2 - (ships / 2) + x][y2] = '#';
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
			} else if (board[x][y] == 'X') {
				board2[x][y] = 'X';
			} else {
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
					board[x2 - 1][y2 - (ships / 2) + y] = '#';
				}
				ship_settle = false;
			}
		}
		else {
			spacetest = vspace_test(board, ships, x2, y2);
			if (spacetest) {
				for (int x = 0; x < ships; x++) {
					board[x2 - (ships / 2) + x][y2 - 1] = '#';
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

//For now, undecided variables for shoot() function. Testing variable usage of x1 and y1.
void shoot(char board[16][16], int x1, int y1)
{
	std::cout << "Where would you like to aim? \nX-value?" << std::endl;
	std::cin >> x1;
	std::cout << "Y-value?" << std::endl;
	std::cin >> y1;
	bool hit = check_hit(x1 - 1, y1 - 1, board);
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
void ai_shoot(char board[16][16], int orientation, int xai, int yai)
{
	if (orientation == 0) {
		int xai = std::rand() % 15;
		int yai = std::rand() % 15;

		bool hit = check_hit(xai, yai, board);
		if (hit) {
			board[xai][yai] = 'H';
			std::cout << "You've been hit!" << std::endl;
			orientation = 4;
		}
		else {
			board[xai][yai] = 'X';
			std::cout << "Enemy missed!" << std::endl;
		}
	}
	else if (orientation == 1) {
		bool hit = check_hit(xai + 1, yai, board);
		if (hit) {
			board[xai + 1][yai] = 'H';
			std::cout << "You've been hit!" << std::endl;
		}
		else {
			board[xai + 1][yai] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
	}
	else if (orientation == 2) {
		bool hit = check_hit(xai, yai + 1, board);
		if (hit) {
			board[xai][yai + 1] = 'H';
			std::cout << "You've been hit!" << std::endl;
		}
		else {
			board[xai][yai + 1] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
	}
	else if (orientation == 3) {
		bool hit = check_hit(xai - 1, yai, board);
		if (hit) {
			board[xai - 1][yai] = 'H';
			std::cout << "You've been hit!" << std::endl;
		}
		else {
			board[xai - 1][yai] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
	}
	else if (orientation == 4) {
		bool hit = check_hit(xai, yai - 1, board);
		if (hit) {
			board[xai][yai - 1] = 'H';
			std::cout << "You've been hit!" << std::endl;
		}
		else {
			board[xai][yai - 1] = 'X';
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
	}
}

bool check_hit(int x, int y, char board[16][16])
{
	if (board[x][y] == '#')
		return true;
	return false;
}

//function name "life_test" undecided. Also requesting possible shortening of code.
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
		if (board[x2 - 1][y2 - (ships / 2) + y] == ' ') {
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
		if (board[x2 - (ships / 2) + x][y2 - 1] == ' ') {
			vspacetest++;
		}
	}
	if (vspacetest == ships)
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

