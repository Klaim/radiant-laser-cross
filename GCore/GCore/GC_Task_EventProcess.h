#ifndef GCORE_TASK_EVENTPROCESS_H
#define GCORE_TASK_EVENTPROCESS_H
#pragma once

#include "GC_Common.h"

#include "GC_Task.h"

namespace gcore
{
	template< typename TypeId > class EventManager;

	/** Task that update an EventManager by calling it's EventManager::processEvents() function each cycle.

		@see Task
		@see EventManager
		
	*/
	template< typename EventTypeId >
	class GCORE_API Task_EventProcess  : public Task
	{
	public:

		typedef EventManager< EventTypeId > EventManagerType;

		/** Constructor.
			@param eventManager EventManager that this Task will update.
		*/
		Task_EventProcess(EventManagerType& eventManager, TaskPriority priority = TaskPriority() ,const std::string& name = std::string() )
			:Task( priority , name ),
			m_eventManager(eventManager)
		{

		}

		~Task_EventProcess();

		EventManagerType& eventManager() { return m_eventManager; }

	protected:

		virtual void onActivate(){};
		virtual void onTerminate(){};

		/** Update the EventManager by calling EventManager::processEvents().		
			@see EventManager
		*/
		virtual void execute()
		{
			m_eventManager.process();
		}


	private:

		///EventManager to update
		EventManagerType& m_eventManager;


	};


	

}

#endif