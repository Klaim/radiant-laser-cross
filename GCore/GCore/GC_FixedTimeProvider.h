#ifndef GCORE_FIXEDTIMEPROVIDER_H
#define GCORE_FIXEDTIMEPROVIDER_H
#pragma once

#include "GC_Common.h"
#include "GC_TimeReference.h"

namespace gcore
{



	/** Provide time based on a fixed time update. Used for debugging time dependant features.
	*/
	class FixedTimeProvider : public TimeReference
	{
	public:

		/** Constructor.
		*/
		FixedTimeProvider( TimeValue fixedTime )
			: TimeReference()
			, m_fixedTime( fixedTime )
			, m_currentTimeSinceStart( 0 )
		{
		}

		/** Destructor.
		*/
		~FixedTimeProvider(){}

		/** Time passed since the system started (or other base time reference, implementation-specific).
			@return Time value (in seconds).
		*/
		TimeValue getTimeSinceStart() const 
		{
			m_currentTimeSinceStart += m_fixedTime;
			return m_currentTimeSinceStart;
		}

	protected:

	private:

		/// Fixed time used to increment the current time each time 
		const TimeValue m_fixedTime;

		/// Virtual time passed since the system start.
		mutable TimeValue m_currentTimeSinceStart;

	};

}

#endif