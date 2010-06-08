#include "GC_Task.h"
#include "GC_TaskManager.h"

namespace gcore
{
	
	Task::Task( TaskPriority priority /*= 0 */,const std::string& name /*= "" */ ) : m_name( name ), 
		m_priority( priority ), 
		m_state( TS_UNREGISTERED ),
		m_taskManager( nullptr )
	{

	}

	Task::~Task()
	{
		if( m_taskManager = nullptr )
		{
			m_taskManager->unregisterTask( *this );
		}
	}

	void Task::activate()
	{
		GC_ASSERT_RETURN( m_taskManager != nullptr , "Tried to activate an unregistered Task : null TaskManager !" );  
		GC_ASSERT_RETURN( m_state != TS_UNREGISTERED , "Inconsistent state !" );  
		m_taskManager->activateTask( *this );
	}

	void Task::pause()
	{
		GC_ASSERT_RETURN( m_taskManager != nullptr , "Tried to pause an unregistered Task! : null TaskManager !" );  
		GC_ASSERT_RETURN( m_state != TS_UNREGISTERED , "Inconsistent state !" );  
		m_taskManager->pauseTask( *this );
	}

	void Task::resume()
	{
		GC_ASSERT_RETURN( m_taskManager != nullptr , "Tried to pause an resume Task! : null TaskManager !" );  
		GC_ASSERT_RETURN( m_state != TS_UNREGISTERED , "Inconsistent state !" );  
		m_taskManager->resumeTask( *this );
	}

	void Task::terminate()
	{
		GC_ASSERT_RETURN( m_taskManager != nullptr , "Tried to terminate an unregistered Task! : null TaskManager !" );  
		GC_ASSERT_RETURN( m_state != TS_UNREGISTERED , "Inconsistent state !" );  
		m_taskManager->terminateTask( *this );
	}

	void Task::unregister()
	{
		GC_ASSERT_RETURN( m_taskManager != nullptr , "Tried to unregister an unregistered Task! : null TaskManager !" );  
		GC_ASSERT_RETURN( m_state != TS_UNREGISTERED , "Inconsistent state !" );  
		m_taskManager->unregisterTask( *this );
	}

	void Task::priority( const TaskPriority& priority )
	{
		if( m_taskManager != nullptr ) m_taskManager->changeTaskPriority( *this, priority );
		else m_priority = priority;
	}
}