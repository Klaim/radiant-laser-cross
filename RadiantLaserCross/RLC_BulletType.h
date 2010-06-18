#ifndef RLC_BULLETTYPE_H
#define RLC_BULLETTYPE_H
#pragma once

#include <boost/shared_ptr.hpp>

#include "sfml/Graphics/Shape.hpp"
#include "sfml/Graphics/Color.hpp"

namespace rlc
{
	class Bullet;

	/** No documentation yet.
	*/
	class BulletType
	{
	public:
		
		virtual sf::Shape bullet_shape() const = 0;
		virtual sf::Color bullet_color() const = 0;
		virtual float bullet_speed() const = 0;
		virtual void bullet_behavior( Bullet& bullet ) const = 0;
		
	private:

	};

	typedef boost::shared_ptr< BulletType > BulletTypePtr;
	
}

#endif