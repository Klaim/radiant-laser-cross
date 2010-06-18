#include "RLC_Bullet.h"

#include "sfml/Graphics/RenderWindow.hpp"

#include "RLC_Game.h"
#include "RLC_GameScene.h"

namespace rlc
{
	
	Bullet::Bullet()
		: m_velocity()
		, m_type()
		, m_alive(false)
	{
		core( Box( 0.0f, 0.0f, 3.0f, 3.0f ) );
	}

	void Bullet::fire( const BulletTypePtr& bullet_type, Position start_pos, Direction start_dir )
	{
		GC_ASSERT_NOT_NULL( bullet_type.get() );

		m_type = bullet_type;

		position( start_pos );
		m_velocity = start_dir * bullet_type->bullet_speed();

		m_alive = true;
		GameScene::instance().add( this );
	}

	void Bullet::do_update()
	{
		if( !m_type.get() )
		{
			die();
			return;
		}

		m_type->bullet_behavior( *this );

		if( is_alive() )
		{
			move_forward();

			if( !in_screen( *this ) )
			{
				die();
			}
		}


	}

	void Bullet::do_render()
	{
		if( !m_type.get() )
		{
			die();
			return;
		}

		sf::Shape shape = m_type->bullet_shape();
		shape.SetPosition( position() );
		shape.SetRotation( orientation() );

		Game::current().display().Draw( shape );
	}

	void Bullet::move_forward()
	{
		Position new_pos = position();
		new_pos += m_velocity;
		position( new_pos );
	}

	void Bullet::die()
	{
		m_alive = false;

		GameScene::instance().remove( this );

		m_type.reset();
		m_velocity = Velocity();
	}

}