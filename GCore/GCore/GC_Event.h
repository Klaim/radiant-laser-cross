#ifndef GCORE_EVENT_H
#define GCORE_EVENT_H
#pragma once

#include <string>

#include "GC_Common.h"

namespace gcore
{

	/** Event object base class.
		
		An Event is sent in an EventManager that will reroute
		it to it's registered EventListeners that listen to the same TypeId.
		@par
		This class alone is enough to manage simple events. In the case
		of an event that should provide data, you should use this class as
		base class.
		@remark
		An event can sent to the appropriate EventListeners in an immediate way 
		or in a buffered way. See EventManager class for more details.
		@see EventManager

	*/
	template< typename TypeId >
	class Event
	{
	public:

		///Event type id.
		typedef TypeId type_id;
	
		/** Constructor.
			@param type Type of this event.
		*/
		Event( type_id type )
			:m_type(type)
		{}
		
		virtual ~Event(){}

		/** Event type id value.
			@return Type id of this event.
		*/
		type_id type() const {return m_type;}
	
	private:

		///Event type value. It is not constant to make the Event class serializable if necessary.
		const type_id m_type;

	};

	
}

#endif