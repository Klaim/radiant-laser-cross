#ifndef GC_PHASEMANAGER_H
#define GC_PHASEMANAGER_H
#pragma once

#include <unordered_map>
#include <vector>

#include "GC_Common.h"
#include <string>

#include "GC_Phase.h"

namespace gcore
{
		
	/** Utility tool for managing several Phases in one object.
		
	*/
	class GCORE_API PhaseManager 
	{
	public:
		PhaseManager();

		~PhaseManager();

		/** Register a phase.
			@param phase Phase to register.
		*/
		void registerPhase( const PhasePtr& phase );

		/** Unregister a registered phase.
			@param phaseName Name of the phase to unregister.
		*/
		void unregisterPhase( const std::string& phaseName ) { unregisterPhase( findRegisteredPhase( phaseName ) ); }
		void unregisterPhase( const PhasePtr& phase );


		/** Request a phase to load.
			@param phaseName Name of the registered phase to load.
		*/
		void requestLoadPhase( const std::string& phaseName ){ requestLoadPhase( findRegisteredPhase( phaseName ) ); }
		void requestLoadPhase( const PhasePtr& phase );
		
		/** Request a phase to load.
			@param phaseName Name of the registered phase to unload.
		*/
		void requestUnloadPhase( const std::string& phaseName ){ requestUnloadPhase( findRegisteredPhase( phaseName ) ); }
		void requestUnloadPhase( const PhasePtr& phase );


		/** Request a phase to load.
			@param phaseName Name of the registered phase to activate.
		*/
		void requestActivatePhase( const std::string& phaseName ){ requestActivatePhase( findRegisteredPhase( phaseName ) ); }
		void requestActivatePhase( const PhasePtr& phase );

		/** Request a phase to load.
			@param phaseName Name of the registered phase to terminate.
		*/
		void requestTerminatePhase( const std::string& phaseName ){ requestTerminatePhase( findRegisteredPhase( phaseName ) ); }
		void requestTerminatePhase( const PhasePtr& phase );

		/** Unregister all registered phases.
		*/
		void unregisterAllPhases();


		/** Find a registered phase by it's name.
		@param phaseName Name of the registered phase to retrieve.
		@return The requested phase or null if not found.
		*/
		PhasePtr findPhase( const std::string& phaseName );

		/** Find a registered phase by it's name and throw an exception if not found!
		@return The requested phase. Will throw an exception if the phase is not found.
		*/
		PhasePtr findRegisteredPhase( const std::string& phaseName );


		/** Get a list of registered phases' names.
		*/
		std::vector< std::string > getRegisteredPhaseNames() const;

	protected:
		
	private:

		typedef std::tr1::unordered_map< std::string,  PhasePtr > PhaseIndex;

		/// phase index
		PhaseIndex m_phaseIndex;

		// non copyable
		PhaseManager(const Phase& ohterPhase);
		void operator=(const Phase& ohterPhase); 

		
	};
	

}

#endif