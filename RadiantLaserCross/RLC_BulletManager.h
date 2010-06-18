#ifndef RLC_BULLETMANAGER_H
#define RLC_BULLETMANAGER_H
#pragma once

#include <vector>

#include "GC_Singleton.h"

#include "RLC_Bullet.h"
#include "RLC_BulletType.h"

namespace rlc
{
	/** No documentation yet.
	*/
	class BulletManager 
		: public gcore::Singleton< BulletManager >
	{
	public:

		void reset( unsigned long max_bullets );

		void fire_bullet( const BulletTypePtr& bullet_type, Position start_pos, Direction start_dir );
		
	private:

		typedef std::vector< Bullet > Bullets;
		Bullets m_bullets;

		Bullets::iterator find_dead_bullet();
	
	};
	
}

#endif