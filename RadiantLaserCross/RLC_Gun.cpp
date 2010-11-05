#include "RLC_Gun.h"

#include "RLC_BulletManager.h"

#include "sfml/Graphics/Matrix3.hpp"
#include "sfml/System/Vector2.hpp"

namespace rlc
{
	

	Gun::Gun( GunTypePtr gun_type )
		: m_type( gun_type )
		, m_direction( 1.0f, 0.0f )
		, m_heat( 0.0f )
	{
		GC_ASSERT_NOT_NULL( m_type );
	}

	void Gun::fire()
	{
		GC_ASSERT_NOT_NULL( m_type );
		if( m_heat <= 0.0f )
		{
			BulletManager::instance().fire_bullet( m_type->bullet_type(), position() + cannon(), m_direction );
			m_heat += m_type->fire_rate();
		}
		
	}
	
	void Gun::direction( Orientation angle )
	{
		sf::Matrix3 transformation;
		transformation.SetFromTransformations( sf::Vector2f(), sf::Vector2f(), angle, sf::Vector2f( 1.0f, 1.0f) );

		m_direction = transformation.Transform( Vector2( 1.0f, 0.0f ) );
		m_current_cannon = transformation.Transform( m_cannon );
	}

	void Gun::cannon( Position new_cannon )
	{
		m_cannon = new_cannon;
		m_current_cannon = m_cannon;
	}


	void Gun::do_update()
	{
		cool();
	}

	void Gun::cool()
	{
		if( m_heat > 0.0f )
		{
			m_heat -= 1.0f;
			if( m_heat < 0.0f )
				m_heat = 0.0f;
		}
	}


	
}