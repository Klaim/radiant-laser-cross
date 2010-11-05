#include "RLC_GameStateManager.h"

#include "RLC_Game.h"

namespace rlc
{

	void GameStateManager::add( GameStatePtr game_state )
	{
		GC_ASSERT_NOT_NULL( game_state );
		GC_ASSERT(  ! game_state->name().empty() , "Tried to register a game state with an empty name!" );

		if( m_state_index.find( game_state->name() ) != m_state_index.end() )
		{
			GC_EXCEPTION << "Tried to add a game state with a name already registered : " << game_state->name();
		}

		// register the state
		m_state_index.insert( std::make_pair( game_state->name(), game_state ) );

	}



	void GameStateManager::switch_to( const std::string& state_name )
	{
		GC_ASSERT( !state_name.empty() , "Tried to register a game state with an empty name!" );

		auto find_it = m_state_index.find( state_name );

		if( find_it == m_state_index.end() )
		{
			GC_EXCEPTION << "Tried to switch to a game state with non registered name : " << state_name;
		}
		
		GameStatePtr next_state = find_it->second;
		
		GC_ASSERT_NOT_NULL( next_state );

		RLC_LOG << "---------------------------------------------------------";
		RLC_LOG << "-- Switching to " << next_state->name() << " state ... -- ";
		
		if( m_current_state != nullptr )
		{
			//end the current state
			RLC_LOG << "Ending state " << m_current_state-> name() << " ...";
			m_current_state->end();
			RLC_LOG << "Ended state " << m_current_state-> name() << ".";
		}

		// now set the new state
		m_current_state = next_state;

		// begin the next state
		RLC_LOG << "Beginning state " << m_current_state-> name() << " ...";
		m_current_state->begin();
		RLC_LOG << "Began state " << m_current_state-> name() << ".";

		RLC_LOG << "-- Switching done. -- ";
		RLC_LOG << "---------------------------------------------------------";
	}



	void GameStateManager::update()
	{
		if( m_current_state != nullptr )
		{
			m_current_state->update();
		}
	}

	void GameStateManager::render()
	{
		if( m_current_state != nullptr )
		{
			m_current_state->render();
		}
	}


}