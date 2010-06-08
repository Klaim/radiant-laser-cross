#ifndef RLC_PLAYERSHIP_H
#define RLC_PLAYERSHIP_H
#pragma once

#include <array>

#include "RLC_Ship.h"
#include "RLC_Gun.h"

namespace rlc
{
	const unsigned int MAX_PLAYER_GUNS = 4;
	
	/** No documentation yet.
	*/
	class PlayerShip
		: public Ship< MAX_PLAYER_GUNS >
	{
	public:

		PlayerShip();
		
	private:

		void do_render();
		void do_update();

		void update_move();
	};
	
}

#endif