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
	template< unsigned int MAX_GUN_COUNT > // specialize for 0 ?
	class Ship
		: public GameEntity
	{
	public:

		Ship(){}

		void fire_gun( unsigned int gun_idx ) 
		{ 
			GunSlot gun_slot = m_guns.at( gun_idx );
			if( gun_slot.get() != nullptr ) 
			{
				gun_slot->fire();
			}

		}

	protected:

		// ? guns access? add/remove guns?
		
	private:
		
		std::array< GunSlot, MAX_GUN_COUNT > m_guns;
	};



}

#endif