#ifndef RLC_GUN_H
#define RLC_GUN_H
#pragma once

#include "RLC_GameEntity.h"
#include "RLC_GunType.h"

#include <boost/shared_ptr.hpp>


namespace rlc
{
	
	/** No documentation yet.
	*/
	class Gun
		: public GameEntity
	{
	public:

		Gun( GunTypePtr gun_type );

		void fire();
		void cool();

		void direction( Orientation angle  );
		void direction( Direction new_direction ) { m_direction = new_direction; }
		Direction direction() const { return m_direction; }

		void cannon( Position new_cannon ) { m_cannon = new_cannon; }
		Position cannon() const { return m_cannon; }
		
	private:

		void do_update();

		Direction m_direction; 
		Position m_cannon; // relative to the ship?
		const GunTypePtr m_type;
		float m_heat;
	};

	typedef boost::shared_ptr< Gun > GunSlot;
	
}

#endif