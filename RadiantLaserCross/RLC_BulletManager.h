#ifndef RLC_BULLETMANAGER_H
#define RLC_BULLETMANAGER_H
#pragma once

#include <array>

#include "GC_Singleton.h"

#include "RLC_Bullet.h"
#include "RLC_BulletType.h"
#include "RLC_BulletPool.h"

namespace rlc
{
	namespace config
	{
		static const std::size_t MAX_BULLETS = 300;
	}


	/** No documentation yet.
	*/
	class BulletManager
		: public gcore::Singleton< BulletManager >
	{
	public:

		void fire_bullet( const BulletTypePtr& bullet_type, Position start_pos, Direction start_dir );
		
	private:
		
		BulletPool< config::MAX_BULLETS > m_bullets_pool;

	};
	
}

#endif