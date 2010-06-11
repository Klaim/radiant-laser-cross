#include "RLC_Bullet.h"


namespace rlc
{
	
	Bullet::Bullet( BulletTypePtr bullet_type )
		: m_rotation_speed()
		, m_type( bullet_type )
	{

	}

	void Bullet::fire( Position start_pos, Velocity velocity )
	{
		position( start_pos );
		
	}

	void Bullet::do_update()
	{

	}

	void Bullet::do_render()
	{

	}

}