#include "RLC_GameEntity.h"

#include "sfml/Graphics/Rect.hpp"

#include "RLC_GameConfig.h"

namespace rlc
{
	

	sf::Shape GameEntity::core_shape()
	{
		sf::Shape result_shape = sf::Shape::Rectangle( m_core.Top, m_core.Left, m_core.Bottom, m_core.Right, sf::Color::Green, 1.0f );

		result_shape.Rotate( m_orientation );

		result_shape.SetPosition( m_position );

		return result_shape;
	}

	void GameEntity::position( Position new_pos )
	{
		Vector2 translation = new_pos - m_position;
		m_position = new_pos;

		for( Entities::const_iterator it = children().begin(); it != children().end(); ++it )
		{
			(*it)->position( (*it)->position() + translation );
		}
	}

	bool in_screen( const GameEntity& entity )
	{
		sf::FloatRect screen_rect( 0.0f, 0.0f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT) );
		sf::FloatRect entity_core = entity.core();
		entity_core.Offset( entity.position().x, entity.position().y );
		return screen_rect.Intersects( entity_core ); 
	}

}