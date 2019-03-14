// BattleShipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* 
*   Optional TODO:
*------------------------
*	-Display both Boards (requires change in DisplayBoard function, OOP can simplify problem)
*   -Coordanate bug with letters (try catch function probably required)
*	-Make Object Oriented (add classes)
*		+(Requires OOP) Flexible Board Size (and number of ships)
*		+Score Board
*		+Identify and announce ships and ship deaths, respectively
*		+Track Placement for 5 turns
*		+Developer options
*		+Abilities
*/




#include "pch.h"
#include <iostream>
//Library includes random to create random inputs by the "ai".
#include <cstdlib>
//Libary included to create truly random numbers with the libary above random functions.
#include <ctime>

//DisplayBoard() to show all of the player's board values to them.
void DisplayBoard(int board[11][11], int arrx, int arry);

//set_board() to initially set all values of the board to O.
void set_board(int board[11][11], int arrx, int arry);

//ai_set_ship() to set the enemy's board via random input.
void ai_set_ship(int board[11][11], int w, int ships, int arrx, int arry);

//updateboard() to update the top board to the show the same as the ai board, but without the ships.
void updateboard(int board[11][11], int board2[11][11]);

//set_ship() to set up the player's ships with their inputs. Also resets int values so it may be used again.
void set_ship(int board[11][11], int ships, int w, int arrx, int arry, int x2 = 0, int y2 = 0);

//shoot() to recieve input from the player and input into the check_hit() function, and outputs whether or not the shot hit or missed.
void shoot(int board[11][11], int x1, int y1, int arrx, int arry);

//ai_shoot() to generate random numbers and input it into a check_hit() function, and outputs whether or not the shot hit or missed.
void ai_shoot(int board[11][11], int &orientation, int &xai, int &yai, int arrx, int arry);

//check_hit() to check the board for whether or not the input was successful or not, and outputs the answer to the shoot() function.
bool check_hit(int x, int y, int board[11][11], bool &duplicateShot, int arrx, int arry);
bool check_hit(int x, int y, int board[11][11], bool &duplicateShot, bool &not_on_board, int arrx, int arry);
bool check_hit(int x, int y, int board[11][11], bool &duplicateShot, bool &not_on_board, bool &shipShot, int arrx, int arry);

//life_test() to check if any of a player's ships are alive. Will end the game if no ship spaces are found on either board.
bool life_test(int board[11][11], int arrx, int arry);

//hspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for horizontal orientation.
bool hspace_test(int board[11][11], int ships, int x2, int y2);

//vspace_test() to check if places chosen by the player for their ships will overlap other ships and/or clip out of the board for vertical orientation.
bool vspace_test(int board[11][11], int ships, int x2, int y2);

//main() to start the thing.
void main()
{
	srand((unsigned)time(0));
	int xai = 0;
	int yai = 0;
	int orientation = 0;
	int turn_counter = 1;
	//For use in changing the board later on.
	int arrx = 10;
	int arry = 10;
	//Keeps track of every ship, even when playing classic Battleship (10 x 10)
	int ships[5] = { 5, 4, 3, 3, 2 };
	int bottom_board[11][11] = {};
	int top_board[11][11] = {};
	int ai_board[11][11] = {};

	set_board(top_board, arrx, arry);
	set_board(bottom_board, arrx, arry);
	set_board(ai_board, arrx, arry);

	DisplayBoard(bottom_board, arrx, arry);

	for (int w = 1; w <= 5; w++) {
		set_ship(bottom_board, ships[w], w, arrx, arry);
		system("cls");

		DisplayBoard(bottom_board, arrx, arry);

		ai_set_ship(ai_board, w, ships[w], arrx, arry);

	}

	bool lifetest = life_test(bottom_board, arrx, arry);
	bool ailifetest = life_test(ai_board, arrx, arry);

	//This maybe a good while loop :)
	while (lifetest && ailifetest) {
		shoot(ai_board, 0, 0, arrx, arry);

		updateboard(ai_board, top_board);
		system("cls");

		DisplayBoard(top_board, arrx, arry);

		ailifetest = life_test(ai_board, arrx, arry);

		if (!ailifetest) {

			std::cout << "You win!" << std::endl;

			DisplayBoard(ai_board, arrx, arry);

			std::cout << "Turns taken: " << turn_counter << std::endl;
			return;

		}

		ai_shoot(bottom_board, orientation, xai, yai, arrx, arry);

		DisplayBoard(bottom_board, arrx, arry);

		lifetest = life_test(bottom_board, arrx, arry);

		if (!lifetest) {

			std::cout << "You lost!" << std::endl;

			DisplayBoard(ai_board, arrx, arry);

			std::cout << "Turns taken: " << turn_counter << std::endl;
			return;

		}

		turn_counter++;
	}
}

void DisplayBoard(int board[11][11], int arrx, int arry)
{
	//Keeps track of every tile. # tiles are ship tiles and are anything above 3.
	char z = 'A';

	std::cout << "  |";

	for (int a = 1; a < arrx + 1; a++) 
	{

		if (a < 10)
			std::cout << a << "  ";

		else
			std::cout << a << " ";

	}

	std::cout << std::endl;

	std::cout << "--|";
	for (int t = 0; t < arrx; t++)
		std::cout << "---";

	std::cout << std::endl;

	for (int x = 0; x < arrx; x++) {
		std::cout << z << " |";
		z++;

	for (int y = 0; y < arry; y++)
		//use of board int, DONT change to char or it will BREAK!!!!!!!!
		switch (board[x][y]) {

		case 1:
			std::cout << ' ' << "  ";
			break;
		
		case 2:
			std::cout << 'X' << "  ";
			break;
		
		case 3:
			std::cout << 'H' << "  ";
			break;
		
		default:
			std::cout << '#' << "  ";
			break;
			}
		}

		std::cout << std::endl;
	}
}

void set_board(int board[11][11], int arrx, int arry)
{
	for (int x = 0; x < arrx; x++) {

		for (int y = 0; y < arry; y++)

			board[x][y] = 1;
	}

}

void ai_set_ship(int board[11][11], int w, int ships, int arrx, int arry)
{

	bool ship_probs = false;
	bool spacetest = false;
	int x2 = std::rand() % arrx;
	int y2 = std::rand() % arry;
	int position = std::rand() % 2;
	if (position == 0) {

		spacetest = hspace_test(board, ships, x2, y2);
	
		if (spacetest) {
			for (int y = 0; y < ships; y++)
				
board[x2][y2 - (ships / 2) - 1 + y] = w + 3;
			ship_probs = false;
		}
	}

	else 
	{
		spacetest = vspace_test(board, ships, x2, y2);

		if (spacetest) 
		{
			for (int x = 0; x < ships; x++)
				board[x2 - (ships / 2) - 1 + x][y2] = w + 3;

			ship_probs = false;

		}
		if (!spacetest)
			ship_probs = true;

		if (ship_probs)
			ai_set_ship(board, w, ships, arrx, arry);
}

void updateboard(int board[11][11], int board2[11][11])
{
	for (int x = 0; x < 10; x++) {

		for (int y = 0; y < 10; y++) {

			if (board[x][y] == 3)
				board2[x][y] = 3;

			else if (board[x][y] == 2)
				board2[x][y] = 2;

			else
				board2[x][y] = 1;
		}
	}
}

//Figure out a way to set int position to a bool value instead of a number?
void set_ship(int board[11][11], int ships, int w, int arrx, int arry, int x2, int y2)
{
	bool ship_probs = false;
	bool spacetest = false;
	int position = 0;

	std::cout << "Where would you like to place your ship?" << std::endl;
	std::cin >> x2 >> y2;
	if (x2 >= arrx || y2 >= arry || x2 < 0 || y2 < 0) {
		std::cout << "Invalid." << std::endl;
		set_ship(board, ships, ships, w, arrx, arry);
	}

	else 
	{
		std::cout << "1: Horizontal \n2: Vertical" << std::endl;
		std::cin >> position;
		if (position == 1) {
			spacetest = hspace_test(board, ships, x2, y2);

			if (spacetest) {
				for (int y = 0; y < ships; y++)
					board[x2 - 1][y2 - (ships / 2) - 1 + y] = w + 3;

				ship_probs = false;

			}
		}

		else if (position == 2) {
			spacetest = vspace_test(board, ships, x2, y2);

			if (spacetest) {
				for (int x = 0; x < ships; x++)
					board[x2 - (ships / 2) - 1 + x][y2 - 1] = w + 3;

				ship_probs = false;

			}
		}
		else {
			std::cout << "Please try again0" << std::endl;
		}

		if (!spacetest) {
			std::cout << "Invalid position." << std::endl;
			ship_probs = true;
		}

		if (ship_probs)
			set_ship(board, ships, w, arrx, arry, x2, y2);
	}
}

void shoot(int board[11][11], int x1, int y1, int arrx, int arry)
{
	bool hit = false;
	bool duplicateShot = false;
	bool not_on_board = false;

	std::cout << "Where would you like to aim?" << std::endl;
	std::cin >> x1 >> y1;
	hit = check_hit(x1 - 1, y1 - 1, board, duplicateShot, not_on_board, arrx, arry);
	
	if (duplicateShot)
		std::cout << "Already shot there. Please try again." << std::endl;
	
	if (not_on_board)
		std::cout << "Inputs are not on the board. Please try again." << std::endl;
	
	if (duplicateShot || not_on_board)
		shoot(board, x1, y1, arrx, arry);
	
	else {
		std::cout << "You fired at " << x1 << ", " << y1 << std::endl;
		if (hit) {
			board[x1 - 1][y1 - 1] = 3;
			std::cout << "Hit!" << std::endl;
		}
		else {
			board[x1 - 1][y1 - 1] = 2;
			std::cout << "Miss!" << std::endl;
		}
	}
}

void ai_shoot(int board[11][11], int &orientation, int &xai, int &yai, int arrx, int arry)
{
	int ptrxai = xai;
	int ptryai = yai;
	bool duplicateShot = false;
	bool hit = false;
	bool not_on_board = false;
	bool shipShot = false;

	switch (orientation) 
	{
	case 1: {
		hit = check_hit(xai + 1, yai, board, duplicateShot, not_on_board, shipShot);

		if (shipShot) {
			ptrxai++;
			break;
		}

		if (duplicateShot || not_on_board) {
			orientation--;
			break;
		}

		std::cout << "Enemy fires at " << xai + 2 << ", " << yai + 1 << std::endl;

		if (hit) {
			board[xai + 1][yai] = 3;
			std::cout << "You've been hit!" << std::endl;
			ptrxai++;
		}

		else {
			board[xai + 1][yai] = 2;
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}

		break;
	}
	case 2: {
		hit = check_hit(xai, yai + 1, board, duplicateShot, not_on_board, shipShot);
		
		if (shipShot) {
			ptryai++;
			break;
		}
		
		if (duplicateShot || not_on_board) {
			orientation--;
			break;
		}

		std::cout << "Enemy fires at " << xai + 1 << ", " << yai + 2 << std::endl;

		if (hit) {
			board[xai][yai + 1] = 3;
			std::cout << "You've been hit!" << std::endl;
			ptryai++;
		}
		
		else {
			board[xai][yai + 1] = 2;
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
		
		break;
	}
	case 3: {
		hit = check_hit(xai - 1, yai, board, duplicateShot, not_on_board, shipShot);

		if (shipShot) {
			ptrxai--;

			if (hit) {
				board[xai + 1][yai] = 2;
				std::cout << "You've been hit!" << std::endl;
				ptrxai++;
			}

			else {
				board[xai + 1][yai] = 1;
				std::cout << "Enemy missed!" << std::endl;
				orientation--;
			}

			break;
		}
		std::cout << "Enemy fires at " << xai << ", " << yai + 1 << std::endl;
		if (hit) {
			board[xai - 1][yai] = 3;
			std::cout << "You've been hit!" << std::endl;
			ptrxai--;
		}
		else {
			board[xai - 1][yai] = 2;
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}
		break;
	}
	case 4: {
		hit = check_hit(xai, yai - 1, board, duplicateShot, not_on_board, shipShot);
		if (shipShot) {
			ptryai--;
			break;
		}

		if (duplicateShot || not_on_board) {
			orientation--;
			break;
		}

		std::cout << "Enemy fires at " << xai + 1 << ", " << yai << std::endl;

		if (hit) {
			board[xai][yai - 1] = 3;
			std::cout << "You've been hit!" << std::endl;
			ptryai--;
		}

		else {
			board[xai][yai - 1] = 2;
			std::cout << "Enemy missed!" << std::endl;
			orientation--;
		}

		break;
	}
	default: {
		int xai = std::rand() % arrx;
		int yai = std::rand() % arry;
		hit = check_hit(xai, yai, board, duplicateShot, arrx, arry);
		
		if (duplicateShot)
			break;
		
		ptrxai = xai;
		ptryai = yai;
		
		std::cout << "Enemy fires at " << xai + 1 << ", " << yai + 1 << std::endl;
		
		if (hit) {
			board[xai][yai] = 3;
			std::cout << "You've been hit!" << std::endl;
			orientation = 4;
		}

		else {
			board[xai][yai] = 2;
			std::cout << "Enemy missed!" << std::endl;
		}

			break;
	
	}
	}

	yai = ptryai;
	xai = ptrxai;

	if (duplicateShot || not_on_board)
		ai_shoot(board, orientation, xai, yai, arrx, arry);
}

bool check_hit(int x, int y, int board[11][11], bool &duplicateShot, bool &not_on_board, int arrx, int arry)
{
	if (x > arrx || y > arry || x < 0 || y < 0)
		not_on_board = true;
	else
		not_on_board = false;

	if (board[x][y] == 2 || board[x][y] == 1) 
		duplicateShot = true;
	else
		duplicateShot = false;

	if (board[x][y] > 2)
		return true;

	return false;
}
bool check_hit(int x, int y, int board[11][11], bool &duplicateShot, int arrx, int arry)
{
	if (board[x][y] == 2 || board[x][y] == 1)
		duplicateShot = true;
	else
		duplicateShot = false;

	if (board[x][y] > 2)
		return true;

	return false;
}
bool check_hit(int x, int y, int board[11][11], bool &duplicateShot, bool &not_on_board, bool &shipShot, int arrx, int arry)
{
	if (x >= arrx || y >= arry || x < 0 || y < 0)
		not_on_board = true;
	else
		not_on_board = false;

	if (board[x][y] == 2)
		shipShot = true;
	else
		shipShot = false;

	if (board[x][y] == 1)
		duplicateShot = true;
	else
		duplicateShot = false;

	if (board[x][y] > 2)
		return true;

	return false;
}

//function name "life_test" undecided.
bool life_test(int board[11][11], int arrx, int arry)
{
	int lifetest = 0;
	for (int x = 0; x < 10; x++) {

		for (int y = 0; y < 10; y++) {

			if (board[x][y] > 3)
				lifetest++;
		}
	}

	if (lifetest >= 1)
		return true;

	return false;
}

bool hspace_test(int board[11][11], int ships, int x2, int y2)
{
	int hspacetest = 0;

	for (int y = 0; y < ships; y++) {
		if (board[x2 - 1][y2 - (ships / 2) - 1 + y] == 1)
			hspacetest++;
		}
	}

	if (hspacetest == ships)
		return true;

	return false;
}
bool vspace_test(int board[11][11], int ships, int x2, int y2)
{
	int vspacetest = 0;

	for (int x = 0; x < ships; x++) {

		if (board[x2 - (ships / 2) - 1 + x][y2 - 1] == 1)
			vspacetest++;
	}

	if (vspacetest == ships)
		return true;

	return false;
}
