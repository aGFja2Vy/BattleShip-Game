#include <iostream>
#include <cstdlib>
#include <ctime>
void shoot();
bool check_hit(int x, int y);
int main()
{
	return 0;
}
void shoot()
{
	char coordinatex;
	char coordinatey;
	std::cout << "Where would you like to aim?\n"

	std::cin >> coordinatex;
	std::cin >> coordinatey;
}
bool check_hit(int x, int y)
{
	if (ai_board[x][y] = '#')
		return true;
	return false;
}