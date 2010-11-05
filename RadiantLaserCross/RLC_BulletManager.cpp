#include "RLC_BulletManager.h"

#include <algorithm>

namespace rlc
{
	void BulletManager::fire_bullet( const BulletTypePtr& bullet_type, Position start_pos, Direction start_dir )
	{
		Bullet* bullet = m_bullets_pool.find_dead_bullet();

		if( bullet )
		{
			// activate the bullet by firing it if fire rate time passed
			bullet->fire( bullet_type, start_pos, start_dir );

		}// no dead bullet available
		// just ignore
		
	}

	
}