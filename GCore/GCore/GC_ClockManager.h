#ifndef GCORE_CLOCKMANAGER_H
#define GCORE_CLOCKMANAGER_H
#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "GC_Common.h"
#include "GC_TimeReference.h"

namespace gcore
{
	class Clock;
	
	/** Create, destroy and manage Clock objects.
		@remark To keep all the managed clocks updated, frequent calls of
		updateClocks should be done.
	*/
	class GCORE_API ClockManager
	{
	public:

		/// Index of clocks by name.
		typedef std::tr1::unordered_map< std::string , Clock*> ClockIndex;

		/// List of clocks.
		typedef std::vector< Clock* > ClockList;

		/** Create a Clock object.
			The name of the Clock must be unique for this ClockManager,
			if not an exception will occurs.
			@param name Name given to the Clock.
			@return A pointer to the new Clock object
		*/
		Clock* createClock(const std::string& name);

		/** Destroy a Clock created by this ClockManager.
			If the Clock object was not created by this ClockManager,
			an exception occurs.
			@param clock Pointer to the Clock to destroy. 
		*/
		void destroyClock(Clock* clock);

		/** Destroy all Clocks created by this ClockManager.
			This will make all pointers to those Clock objects invalid!
		*/
		void destroyAllClocks();

		/** Get a Clock by it's name.
			@param name Clock's name (given at it's creation).
			@return A pointer to the Clock or nullptr if not found.
		*/
		Clock* getClock(const std::string& name);

		/** Update all Clock time.
			@remark This should be called as frequently as possible, 
			each main loop cycle at best.
		*/
		void updateClocks();


		/** Reset all clocks.
		*/
		void reset();

		
		/** @return Time value of the last update, from TimeReference (in seconds).
		*/
		TimeValue getLastUpdateTime() const {return m_lastUpdateTime;}

		/** @return Time elapsed between the last update and the previous one (in seconds).
		*/
		TimeValue getDeltaTime() const {return m_deltaTime;}

		/** @return Maximum time elapsed or 0 or negative value if no limit set (default).                                                                     
		*/
		TimeValue getMaxDeltaTime() const { return m_max_deltaTime; }

		/** Set a maximum limit to the possible delta time or 0 for no limit (default).
		*/
		void setMaxDeltaTime( TimeValue maxDeltaTime )
		{
			GC_ASSERT( maxDeltaTime >= 0, "Max delta time have to be 0 or positive!");
			m_max_deltaTime = maxDeltaTime;
		}

		/** Return the registered Clock list.
		*/
		const ClockList& getClockList() const {return m_clockList;}

		/** Return the named index of all named clocks registered.
		*/
		const ClockIndex& getNamedClocksIndex() const {return m_clockIndex;}


		/** Constructor.
			@param timeReference Provide time used as reference to update all Clocks.
		*/
		ClockManager(const TimeReference& timeReference,  size_t reserveClockCount = 32 );

		/** Destructor.
		*/
		~ClockManager();



	protected:

	private:

		/** Provide time used as reference to update all Clocks.
		*/
		const TimeReference& m_timeReference;

		/** Named index of all the Clocks.
		*/
		ClockIndex m_clockIndex;

		/** List of all Clocks created by this ClockManager.
		*/
		ClockList m_clockList;

		/// Time value of the last update, from TimeReference (in seconds).
		TimeValue m_lastUpdateTime;

		/// Time elapsed between the last update and the previous one (in seconds).
		TimeValue m_deltaTime;

		/// Maximum time elapsed allowed, or 0 or negative value if no limit set.
		TimeValue m_max_deltaTime;

	};

}

#endif