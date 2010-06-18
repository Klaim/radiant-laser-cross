#include "RLC_BulletManager.h"

#include <algorithm>

namespace rlc
{

	void BulletManager::reset( unsigned long max_bullets )
	{
		m_bullets.clear();
		m_bullets.resize( max_bullets );
	}

	
	void BulletManager::fire_bullet( const BulletTypePtr& bullet_type, Position start_pos, Direction start_dir )
	{
		Bullets::iterator bullet_it = find_dead_bullet();

		if( bullet_it == m_bullets.end() )
		{
			// no dead bullet available
			// just ignore
			return;
		}

		// activate the bullet by firing it if fire rate time passed

		bullet_it->fire( bullet_type, start_pos, start_dir );

	}

	BulletManager::Bullets::iterator BulletManager::find_dead_bullet()
	{
		return std::find_if( m_bullets.begin(), m_bullets.end(), []( Bullet& bullet )->bool { return !bullet.is_alive(); } );
	}

}