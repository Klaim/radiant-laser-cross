#include "RLC_Game.h"

int main()
{
	using namespace rlc;

	Game::create();
	Game::instance().run();
	Game::destroy();

	return 0;
}