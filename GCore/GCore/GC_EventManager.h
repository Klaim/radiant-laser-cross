#ifndef GCORE_EVENTMANAGER_H
#define GCORE_EVENTMANAGER_H
#pragma once

#include <algorithm>
#include <unordered_map>
#include <list>
#include <vector>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "GC_Common.h"
#include "GC_Event.h"
#include "GC_EventListener.h"


namespace gcore	
{
	
	/** Manage Events and EventListeners.

		An EventManager will receive all Events that are sent to him
		and reroute them to the appropriate EventListeners that have been registered
		to listen to the event type.
		@par
		The Event objects can be sent in two manners :
		- immediate send : the Event will be sent to the EventListeners immediately;
		- buffered send : the Event is registered and processed later, when EventManager::process() is called.

		@remark
		EventListener objects registered in an EventManager will 
		have been registered to listen to the event type.
		@remark
		An EventListener registered to listen to a null event type will catch all events sent.

	*/
	template< typename EventTypeId >
	class EventManager 
	{
	public:

		

		/// Type of event that can be managed by this manager.
		typedef Event< EventTypeId > EventType;
		typedef boost::shared_ptr< EventType > EventPtr;
		/// Type of listener that this manager can handle.
		typedef EventListener< EventTypeId > EventListenerType;
		
		EventManager();

		/** Clear on destruction.  */
		~EventManager(); 


		/** Register an EventListener to catch events of a specific type.
			@param eventListener EventListener object to register.
			@param typeToCatch Type of the events to catch or a null value to listen to all the events.
		*/
		void addListener( EventListenerType& eventListener, EventTypeId typeToCatch = EventTypeId() );

		/** Unregister an EventListener from catching any event.
			@param eventListener EventListener object to register.
		*/
		void removeListener(EventListenerType& eventListener);


		/** Unregister an EventListener from catching a specific type of event.
			@param eventListener EventListener object to register.
		*/
		void removeListener( EventTypeId typeToCatch, EventListenerType& eventListener);

		/** Remove all EventListeners registered.
		*/
		void removeAllListeners();

		/** Remove all listeners and cancel all buffered events. */
		void clear();

		/** Send an event.
			@remark The Event will no be memory managed. 
			@param eventToSend Event object to send.
			@param immediate If true, the Event will be processed immediately. If false, the Event is registered and will
			be processed on the next call of EventManager::process().
		 */
		void send(const EventPtr& eventToSend , bool immediate=false);

		/** Process all buffered Events.
			For each Event that have not been sent immediately, this will call
			each EventListener::catchEvent() of EventListener registered that have the same
			Event::TypeId than the Event sent.
			@remark EventListeners waiting for an Event::TypeId of value 0 will receive events of all types.
		*/
		void process();


	private:

		typedef std::list< EventListenerType* > EventListenerList;
		typedef std::vector< EventListenerType* > EventListenerBuffer;
		typedef std::tr1::unordered_map< EventTypeId, EventListenerList > EventListenerRegister;
		typedef std::vector< const EventPtr > EventQueue;

		/// Listeners registered for each event type.
		EventListenerRegister m_listenerRegister;

		/// Buffered Events
		EventQueue m_eventQueue;

		/// Event queue used while processing events.
		EventQueue m_processEventQueue;

		/// List of listeners used while processing an event.
		EventListenerBuffer m_processListeners;

		void processEvent( const EventPtr& e );
		void dispatchEvent( const EventPtr& e, EventListenerList& listeners );

	};

	template< typename EventTypeId >
	boost::shared_ptr< Event< EventTypeId > > make_event( EventTypeId type_id )
	{
		return boost::make_shared<Event>( type_id );
	}

	//----------------------------------------------------------------------------------
	// implementation :

	template< typename EventTypeId >
	EventManager<EventTypeId>::EventManager()
	{
		// arbitrary optimizations
		m_processListeners.reserve( 32 ); 

	}


	template< typename EventTypeId >
	EventManager<EventTypeId>::~EventManager()
	{
		clear();
	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::addListener( EventListenerType& eventListener, EventTypeId typeToCatch )
	{
		// get the listeners for this event type or create it
		EventListenerList& listeners = m_listenerRegister[ typeToCatch ]; 

		// check
		GC_ASSERT( std::find( listeners.begin(), listeners.end(), &eventListener ) == listeners.end(), "Tried to add the same listener twice for event " << typeToCatch );

		// register the listener
		listeners.push_back( &eventListener );

	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::removeListener( EventListenerType& eventListener )
	{
		if( m_listenerRegister.empty() )
		{
			GC_ASSERT( !m_listenerRegister.empty(), "Tried to remove a listener from an empty event manager!" );
			return; 
		}

		EventListenerRegister::iterator register_it = m_listenerRegister.begin();

		for( ; register_it != m_listenerRegister.end(); ++register_it )
		{
			EventListenerList& listeners = register_it->second;

			if( listeners.empty() ) continue; // be lazy;

			listeners.remove( &eventListener );
		}

	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::removeListener(  EventTypeId typeToCatch, EventListenerType& eventListener )
	{
		EventListenerRegister::iterator it = m_listenerRegister.find( typeToCatch );

		GC_ASSERT( it != m_listenerRegister.end(), "Tried to remove listener from unregistered event type : " << typeToCatch );

		if( it != m_listenerRegister.end() )
		{
			EventListenerList& listeners = it->second;
			listeners.remove( &eventListener );
		}

	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::removeAllListeners()
	{
		m_listenerRegister.clear();
	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::clear()
	{
		removeAllListeners();
	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::send( const EventPtr& e , bool immediate )
	{
		GC_ASSERT_NOT_NULL( e );

		if( immediate )
		{
			processEvent( e );
		}
		else
		{
			m_eventQueue.push_back( e );
		}

	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::process()
	{
		if( m_eventQueue.empty() ) return; // be lazy!!!

		// first we have to swap the current event queue with the process one (empty)
		m_processEventQueue.clear();
		m_processEventQueue.swap( m_eventQueue ); // ready for the next event sent

		// now we have to process each event in the processing queue
		for( EventQueue::iterator it = m_processEventQueue.begin(); it != m_processEventQueue.end(); ++it )
		{
			EventPtr e = *it;
			GC_ASSERT_NOT_NULL( e );
			processEvent( e );
		}

	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::processEvent( const EventPtr& e )
	{
		GC_ASSERT_NOT_NULL( e );

		if( m_listenerRegister.empty() ) return; // no listener registered at all!

		// first dispatch this event to listeners registered to listen to all events
		EventListenerList& listenAllList = m_listenerRegister[ EventTypeId() ];
		dispatchEvent( e, listenAllList );

		// retrieve the event listener list for this event type if it exists
		EventListenerRegister::iterator register_it = m_listenerRegister.find( e->type() );

		if( register_it == m_listenerRegister.end() ) return; // no listeners for this event!

		// now dispatch the event to those listeners waiting for it
		EventListenerList& listeners = register_it->second;
		dispatchEvent( e, listeners );

	}

	template< typename EventTypeId >
	void EventManager<EventTypeId>::dispatchEvent( const EventPtr& e, EventListenerList& listeners )
	{
		GC_ASSERT_NOT_NULL( e );

		if( listeners.empty() ) return; // be lazy!!

		// prepare this dispatch by copying the listener list in the one used to dispatch
		m_processListeners.reserve( listeners.size() );
		m_processListeners.assign( listeners.begin(), listeners.end() );

		// ok now we have to send the event to all those catchers
		for( EventListenerBuffer::iterator it = m_processListeners.begin(); it != m_processListeners.end(); ++it )
		{
			EventListenerType* listener = *it;
			GC_ASSERT_NOT_NULL( listener );

			listener->catchEvent( *e, *this ); // catch!
		}
	}
	
} // gcore


#endif