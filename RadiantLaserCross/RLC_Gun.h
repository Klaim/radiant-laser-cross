#ifndef RLC_GUN_H
#define RLC_GUN_H
#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

#include "RLC_Bullet.h"

namespace rlc
{
	
	/** No documentation yet.
	*/
	class Gun
	{
	public:

		void fire(); // make it virtual?
		
	private:

		typedef std::vector< Bullet > Bullets;

		Bullets m_bullets;
	
	};

	typedef boost::shared_ptr< Gun > GunSlot;
	
}

#endif