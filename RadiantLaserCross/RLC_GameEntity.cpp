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

	bool in_screen( const GameEntity& entity )
	{
		sf::FloatRect screen_rect( 0.0f, 0.0f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT) );
		return screen_rect.Intersects( entity.core() ); 
	}

}