#ifndef RLC_GUN_H
#define RLC_GUN_H
#pragma once

#include <boost/shared_ptr.hpp>

#include "RLC_Geometry.h"
#include "RLC_GunType.h"

namespace rlc
{
	
	/** No documentation yet.
	*/
	class Gun
	{
	public:

		Gun( GunTypePtr gun_type );

		void fire(); 
		bool fired() const;

		void direction( Orientation angle  ) { /* TODO!!! */ }
		void direction( Direction new_direction ) { m_direction = new_direction; }
		Direction direction() const { return m_direction; }

		void cannon( Position new_cannon ) { m_cannon = new_cannon; }
		Position cannon() const { return m_cannon; }
		
	private:

		Direction m_direction; 
		Position m_cannon; // relative to the ship
		const GunTypePtr m_type;
		
	};

	typedef boost::shared_ptr< Gun > GunSlot;
	
}

#endif