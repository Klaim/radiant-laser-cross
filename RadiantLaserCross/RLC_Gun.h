#ifndef RLC_GUN_H
#define RLC_GUN_H
#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

#include "sfml/System/Vector2.hpp"

#include "RLC_GameEntity.h"
#include "RLC_Bullet.h"

namespace rlc
{
	
	/** No documentation yet.
	*/
	class Gun 
		: public GameEntity
	{
	public:

		Gun();

		void fire(); // make it virtual?
		
	private:

		typedef std::vector< Bullet > Bullets;
		Bullets m_bullets;

		sf::Vector2f m_direction;
		sf::Vector2f m_cannon;

		long free_bullet();
	
	};

	typedef boost::shared_ptr< Gun > GunSlot;
	
}

#endif