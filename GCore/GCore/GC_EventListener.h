#ifndef GCORE_EVENTLISTENER_H
#define GCORE_EVENTLISTENER_H
#pragma once

#include <functional>

#include "GC_Common.h"
#include "GC_Event.h"

namespace gcore
{
	template<typename TypeId> class EventManager;

	/** Receive and manage specific Events.
		
		An EventListener object must be registered in an EventManager to receive
		the Events that the EventManager will receive.
		The EventManager will register the EventListener to catch specific
		event types.
		
		@remark
		This is a virtual base class : the heritor class must define 
		the management of the Event received.
		
		@remark
		An EventListener can be registered by more than one EventManager and
		can listen to more than one type of events.

		@see EventManager, Event

	*/
	template< typename TypeId >
	class EventListener
	{
	public:

		/** User defined Event reception.
			This method will be called when an Event of the type of 
			processed by the EventManager.
			@param e Event that have been sent.
			@param source EventManager that processed the event.
		*/
		virtual void catchEvent(const Event<TypeId>& e, EventManager<TypeId>& source) = 0;

		virtual ~EventListener() {}
	
		/// Function-like object that can catch events.
		typedef typename std::tr1::function< void (const Event<TypeId>& , EventManager<TypeId>& ) > Function;
		
	};


	

	/** Proxy event listener that only redirect event catches to a provided function-like object.*/
	template< typename TypeId >
	class ProxyEventListener : public EventListener< TypeId >
	{
	public:
		ProxyEventListener( const Function& catherFunction )
			: m_catcher_function( catherFunction )
		{}

		inline void catchEvent(const Event< TypeId >& e, EventManager<TypeId>& source)
		{
			m_catcher_function( e, source );
		}

	private:
		
		Function m_catcher_function;
	};

}

#endif