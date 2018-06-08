#include "LifeOfPI.h"

int main()
{
	std::locale::global(std::locale(""));
	std::srand(std::time(0));

	LifeOfPIGame game;
	game.play();
	return 0;
}