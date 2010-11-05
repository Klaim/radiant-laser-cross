#ifndef RLC_GUNTYPE_H
#define RLC_GUNTYPE_H
#pragma once

#include <boost/shared_ptr.hpp>

#include "RLC_BulletType.h"

namespace rlc
{
	/** No documentation yet.
	*/
	class GunType
	{
	public:

		virtual BulletTypePtr bullet_type() const = 0;
		virtual float fire_rate() const = 0;
		
	private:

	};

	typedef boost::shared_ptr< GunType > GunTypePtr;
	
}

#endif