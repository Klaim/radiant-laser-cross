#include <sstream>
#include "GC_ConsoleCmd_TaskControl.h"
#include "GC_Task.h"
#include "GC_Console.h"

namespace gcore
{
	


	ConsoleCmd_TaskControl::ConsoleCmd_TaskControl( const std::string& name, Task& task )
		: ConsoleCommand( name )
		, m_task(task)
	{
		
	}

	ConsoleCmd_TaskControl::~ConsoleCmd_TaskControl()
	{
		
	}

	bool ConsoleCmd_TaskControl::execute( Console & console , const std::vector< std::string >& parameterList )
	{
		if(parameterList.size() != 1)
		{
			printErrorHelpMessage(console);
			return false;
		}
		bool resultOk = false;

		TaskState taskState = m_task.state();
		const std::string& parameter( parameterList.at(0) );

		if(parameter == "start")
		{
			if(taskState == TS_REGISTERED)
			{
				m_task.activate();
				console.printText("Started task " + m_task.name());
			}
			else
			{
				console.printText("/!\\Invalid task state : " + toText(taskState) + " - only " + toText(TS_REGISTERED) + " is valid!" );
			
			}
		}
		else if (parameter == "pause")
		{
			if(taskState == TS_ACTIVE)
			{
				m_task.pause();
				console.printText("Paused task " + m_task.name() );
			}
			else
			{
				console.printText("/!\\Invalid task state : " + toText(taskState) + " - the task have to be " + toText(TS_ACTIVE) + " to be paused!" );
				
			}
		}
		else if (parameter == "resume")
		{
			if(taskState == TS_PAUSED)
			{
				m_task.resume();
				console.printText( "Resumed task " + m_task.name() );
			}
			else
			{
				console.printText("/!\\Invalid task state : " + toText(taskState) + " - the task have to be " + toText(TS_PAUSED) + " to be resumed!" );
				
			}
		}
		else if (parameter == "stop")
		{
			if(taskState != TS_REGISTERED)
			{
				m_task.terminate();
				console.printText("Stopped task " + m_task.name() );
			}
			else
			{
				console.printText("/!\\Invalid task state : " + toText(taskState) + " - the task have to be " + toText(TS_ACTIVE) + " or " + toText(TS_PAUSED) + " to be stopped!" );
				
			}
		}
		else if (parameter == "state")
		{
			console.printText( "Task " + m_task.name() +  " state : "+ toText(taskState) );
		}
		else
		{
			printErrorHelpMessage(console);
		}

		return false;
	}

	void ConsoleCmd_TaskControl::printErrorHelpMessage( Console& console )
	{
		console.printText( "Invalid parameters ! Should be only ONE of the following : ");
		console.printText( " start, pause, resume, stop, state" );
	}

	std::string ConsoleCmd_TaskControl::toText( const TaskState taskState ) const 
	{
		switch( taskState )
		{

		case( TS_ACTIVE ):
			{
				return "ACTIVE";
			}
		case( TS_PAUSED ):
			{
				return "PAUSED";
			}
		case( TS_REGISTERED ):
			{
				return "REGISTERED";
			}
		case( TS_UNREGISTERED ):
			{
				return "UNREGISTERED";
			}

		default:
			{
				std::stringstream errorMsg;
				errorMsg << "Unknown TaskState being translated in text! State value = " ;
				errorMsg << taskState;
				GC_EXCEPTION <<  errorMsg.str();
			}
		}

	}

	std::string ConsoleCmd_TaskControl::help() const
	{
		return	"Help managing a Task via a Console.\n" \
				"It allow the user to link a command to the task in the console and " \
				"use it via it's parameters matching the Task interface : " \
				"\n\n" \
				"Parameter | Call\n" \
				"----------------------------------------------------------\n" \
				"start     | task.activate();\n" \
				"pause     | task.pause();\n" \
				"resume    | task.resume();\n" \
				"stop      | task.pause();\n" \
				"state     | print the current state of the task\n" ;
	}
}