#ifndef RLC_BULLET_H
#define RLC_BULLET_H
#pragma once

#include "RLC_GameEntity.h"
#include "RLC_BulletType.h"

namespace rlc
{
	/** No documentation yet.
	*/
	class Bullet
		: public GameEntity
	{
	public:

		Bullet();
		
		void fire( const BulletTypePtr& bullet_type, Position start_pos, Direction start_dir );

		void die();
		bool is_alive() const { return m_alive; }

		const BulletTypePtr& type() { return m_type; }
		
	private:

		void do_render();
		void do_update();

		void move_forward();

		bool m_alive;
		Velocity m_velocity;
	
		BulletTypePtr m_type;
	};
	
}

#endif