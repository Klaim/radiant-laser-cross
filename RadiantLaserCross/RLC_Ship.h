#ifndef RLC_SHIP_H
#define RLC_SHIP_H
#pragma once

#include <array>

#include "RLC_GameEntity.h"
#include "RLC_Gun.h"

namespace rlc
{
	/** No documentation yet.
	*/
	template< unsigned int MAX_GUN_COUNT >
	class Ship
		: public GameEntity
	{
	public:

		Ship(){}
		
	protected:

		// ? guns access? add/remove guns?
		
	private:
		
		std::array< GunSlot, MAX_GUN_COUNT > m_guns;
	};
	
}

#endif