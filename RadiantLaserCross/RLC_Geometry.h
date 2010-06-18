#ifndef RLC_GEOMETRY_H
#define RLC_GEOMETRY_H
#pragma once


#include "sfml/System/Vector2.hpp"
#include "sfml/Graphics/Rect.hpp"

namespace rlc
{
	const float PI = 3.141592654f;

	typedef short PlanIdx;
	typedef sf::Vector2f Vector2;
	typedef sf::Vector2f Position;
	typedef sf::Vector2f Direction;
	typedef sf::Vector2f Velocity;
	typedef float Orientation;
	typedef sf::FloatRect Box;
		
}

#endif