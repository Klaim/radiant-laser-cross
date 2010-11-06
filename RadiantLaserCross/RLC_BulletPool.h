#ifndef RLC_BULLETPOOL_H
#define RLC_BULLETPOOL_H
#pragma once 

#include <array>
#include <algorithm>
#include <boost/noncopyable.hpp>

namespace rlc
{
	template< std::size_t MAX_BULLETS >
	class BulletPool
		: boost::noncopyable
	{
	public:

		Bullet* find_dead_bullet()
		{
			auto it = std::find_if( m_bullets.begin(), m_bullets.end(), []( Bullet& bullet )->bool { return !bullet.is_alive(); } );
			if( it != m_bullets.end() )
				return &(*it);
			else
				return nullptr;
		}

	private:

		typedef std::array< Bullet, MAX_BULLETS > Bullets;
		Bullets m_bullets;

	};
	
}

#endif 
