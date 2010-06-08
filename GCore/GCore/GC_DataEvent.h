#ifndef GC_DATAEVENT_H
#define GC_DATAEVENT_H
#pragma once

#include <boost/shared_ptr.hpp>

#include "GC_Common.h"

#include "GC_Event.h"

namespace gcore
{
	/** The data event is just a basic event that provide some data witch type is parameterized.
		Use this class for simple events that just hold some informations.
		It's a utility for simple events with some data.
	*/
	template< typename EventTypeId, typename DataType >
	class DataEvent : public Event< EventTypeId >
	{
	public:

		DataEvent( EventTypeId typeId, const DataType& d )
			: Event( typeId )
			, m_data( d )
		{}

		// note : here we assume that NRVO will play a big part to help getting directly the data.
		const DataType& data() const { return m_data; }
		
	protected:
		
	private:
	
		const DataType m_data;

	};

	template< typename EventTypeId, typename DataType >
	boost::shared_ptr< Event< EventTypeId > > make_dataevent( EventTypeId type_id, const DataType& data )
	{
		return boost::make_shared<DataEvent>( type_id, data );
	}

}

#endif