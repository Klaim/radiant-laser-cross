#include "RLC_GameEntity.h"

namespace rlc
{
	

	sf::Shape GameEntity::core_shape()
	{
		sf::Shape result_shape = sf::Shape::Rectangle( m_core.Top, m_core.Left, m_core.Bottom, m_core.Right, sf::Color::Green, 1.0f );

		result_shape.Rotate( m_orientation );

		result_shape.SetPosition( m_position );

		return result_shape;
	}

}