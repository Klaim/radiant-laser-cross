#include "GC_ConsoleCmd_PhaseControl.h"

#include <sstream>

#include "GC_Console.h"

namespace gcore
{
	
	ConsoleCmd_PhaseControl::ConsoleCmd_PhaseControl( const std::string& name, Phase& phase )
		: ConsoleCommand( name )
		, m_phase(phase)
	{
		GC_ASSERT_NOT_NULL( &m_phase );
	}

	ConsoleCmd_PhaseControl::~ConsoleCmd_PhaseControl()
	{
		
	}

	bool ConsoleCmd_PhaseControl::execute( Console & console , const std::vector< std::string >& parameterList )
	{
		if(parameterList.size() != 1)
		{
			printErrorHelpMessage(console);
			return false;
		}
		bool resultOk = false;

		Phase::State phaseState = m_phase.state();
		const std::string& parameter( parameterList.at(0) );

		if(parameter == "load")
		{
			if(phaseState == Phase::UNLOADED)
			{
				console.printText( "Request loading to phase " + m_phase.name());
				m_phase.requestLoad();
			}
			else
			{
				console.printText( "/!\\Invalid phase state : " + toText(phaseState) + " - only " + toText(Phase::UNLOADED) + " is valid!" );
				
			}
		}
		else if (parameter == "activate")
		{
			if(phaseState == Phase::LOADED)
			{
				console.printText( "Request activation to phase " + m_phase.name() );
				m_phase.requestActivate();
			}
			else
			{
				console.printText( "/!\\Invalid phase state : " + toText(phaseState) + " - the phase have to be " + toText(Phase::LOADED) + " to be requested to activate!" );
				
			}
		}
		else if (parameter == "terminate")
		{
			if(phaseState == Phase::ACTIVE)
			{
				console.printText( "Request termination to phase " + m_phase.name() );
				m_phase.requestTerminate();
				
			}
			else
			{
				console.printText( "/!\\Invalid phase state : " + toText(phaseState) + " - the phase have to be " + toText(Phase::ACTIVE) + " to be requested to terminate!" );
				
			}
		}
		else if (parameter == "unload")
		{
			if(phaseState == Phase::LOADED)
			{
				console.printText( "Request unload to phase " + m_phase.name() );
				m_phase.requestUnload();
			}
			else
			{
				console.printText( "/!\\Invalid phase state : " + toText(phaseState) + " - the phase have to be " + toText(Phase::LOADED) + " to be requested to unload!" );
				
			}
		}
		else if (parameter == "state")
		{
			console.printText( "Phase " + m_phase.name() +  " state : "+ toText(phaseState) );
		}
		else
		{
			printErrorHelpMessage(console);
		}

		return false;
	}

	void ConsoleCmd_PhaseControl::printErrorHelpMessage( Console& console )
	{
		console.printText( "Invalid parameters ! Should be only ONE of the following : ");
		console.printText( " load, unload, activate, terminate, state" );
	}

	std::string ConsoleCmd_PhaseControl::toText( const Phase::State phaseState ) const 
	{
		switch( phaseState )
		{

			/// The phase is unloaded.
		case Phase::UNLOADED:
			return "UNLOADED";

			/// The phase has been requested to load.
		case 	Phase::LOADING:
			return "LOADING";

			/// The phase is loaded and ready to start.
		case 	Phase::LOADED:
			return "LOADED";

			/// The phase has been requested to unload.
		case 	Phase::UNLOADING:
			return "UNLOADING";

			/// The phase has been requested to activate.
		case 	Phase::ACTIVATING:
			return "ACTIVATING";

			/// The phase is currently active.
		case 	Phase::ACTIVE:
			return "ACTIVE";

			/// The phase has been requested to terminate.
		case 	Phase::TERMINATING:
			return "TERMINATING";

		default:
			{
				std::stringstream errorMsg;
				errorMsg << "Unknown Phase::State being translated in text! State value = " ;
				errorMsg << phaseState;
				GC_EXCEPTION << errorMsg.str();
			}
		}

	}

	std::string ConsoleCmd_PhaseControl::help() const
	{
		return "Manipulate the Phase '" + m_phase.name() + "' by using the parameters: load, activate, terminate, unload.";
	}
}