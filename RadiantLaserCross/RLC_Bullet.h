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

		// TODO : review all that!
		// BulletGenerator?
		Bullet( BulletTypePtr bullet_type );
		
		void fire( Position start_pos, Position direction );

		bool is_active() const { return m_active; }
		
	private:

		void do_render();
		void do_update();

		bool m_active;
		float m_lifetime;
		float m_rotation_speed;
	
		const BulletTypePtr m_type;
	};
	
}

#endif