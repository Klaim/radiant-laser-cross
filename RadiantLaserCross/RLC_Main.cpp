#include "RLC_Game.h"

int main()
{
	using namespace rlc;

	Game::create();
	Game::instance().run();

	return 0;
}