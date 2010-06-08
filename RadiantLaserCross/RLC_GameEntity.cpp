#include "RLC_GameEntity.h"

namespace rlc
{
	

	sf::Shape GameEntity::shape()
	{
		sf::Shape result_shape = sf::Shape::Rectangle( m_box.Top, m_box.Left, m_box.Bottom, m_box.Right, sf::Color::Green, 1.0f );

		result_shape.Rotate( m_orientation );

		result_shape.SetPosition( m_position );

		return result_shape;
	}

}