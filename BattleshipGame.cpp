#include <iostream>
#include <cstdlib>
#include <ctime>

void shoot();
bool check_hit(int x, int y);
void board_change(int x, int y, char board[][]);

int main()
{
	char bottom_board[15][15] = {};
	char top_board[15][15] = {};
	char ai_board[15][15] = {};

	set_board(top_board);
	set_board(bottom_board);
	set_board(ai_board);

	return 0;
}

void set_board(char board[][])
{
	for (int x = 0; x < 15; x++) {
		board[x][0] = 'O';

	}
}

void shoot(char coordinatex, char coordinatey)
{
	std::cout << "Where would you like to aim?\n";
	std::cin >> coordinatex;
	std::cin >> coordinatey;
	bool hit = check_hit(coordinatex, coordinatey, board[][]);
	if (hit)
		array[coordinatex][coordinatey] = 'H';
	else
		array[coordinatex][coordinatey] = 'X';
}

bool check_hit(int x, int y, char board[][])
{
	if (board[x][y] = '#')
		return true;
	return false;
}