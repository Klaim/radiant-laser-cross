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

		
	protected:

		
		void fire_gun( unsigned int gun_idx ); 

		bool has_gun( unsigned int gun_idx ) const { return m_guns.at( gun_idx ).get() != nullptr; }
		GunSlot get_gun( unsigned int gun_idx ) { return m_guns.at( gun_idx ); }

		void set_gun( GunSlot gun, unsigned int gun_idx );
		GunSlot unset_gun( unsigned int gun_idx );
		
		
		unsigned int guns_count() const { return m_guns.size(); }


	private:
		
		std::array< GunSlot, MAX_GUN_COUNT > m_guns;
	};

	template< unsigned int MAX_GUN_COUNT >
	void rlc::Ship<MAX_GUN_COUNT>::fire_gun( unsigned int gun_idx )
	{
		GunSlot gun_slot = m_guns.at( gun_idx );
		if( gun_slot.get() != nullptr ) 
		{
			gun_slot->fire();
		}
	}


	template< unsigned int MAX_GUN_COUNT >
	void rlc::Ship<MAX_GUN_COUNT>::set_gun( GunSlot gun, unsigned int gun_idx )
	{
		GC_ASSERT_NOT_NULL( gun.get() );
		GC_ASSERT_NULL( m_guns.at( gun_idx ).get() );
		m_guns.at( gun_idx ) = gun;
	}

	template< unsigned int MAX_GUN_COUNT >
	GunSlot rlc::Ship<MAX_GUN_COUNT>::unset_gun( unsigned int gun_idx )
	{
		GunSlot& gun_slot = m_guns.at( gun_idx );
		GunSlot gun = gun_slot;
		if( gun.get() != nullptr )
		{
			gun_slot.reset();
			return gun;
		}
	}



}

#endif