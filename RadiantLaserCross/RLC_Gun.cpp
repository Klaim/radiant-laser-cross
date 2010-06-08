#include "RLC_Gun.h"

namespace rlc
{
	
	Gun::Gun()
		: m_direction( 0.0f, 1.0f )
	{
		m_bullets.reserve( 24 );

	}

	void Gun::fire()
	{
		long bullet_idx = free_bullet();

		if( bullet_idx > 0 ) // we still have a bullet ready to be fired!
		{

		}
	}

	long Gun::free_bullet()
	{

		return 0; // TODO : ...
	}

}