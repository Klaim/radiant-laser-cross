#ifndef RLC_GAMESTATEMANAGER_H
#define RLC_GAMESTATEMANAGER_H
#pragma once

#include <unordered_map>
#include <string>

#include "RLC_GameState.h"


namespace rlc
{
	/** No documentation yet.
	*/
	class GameStateManager
	{
	public:

		void add( GameStatePtr game_state );
		void update();
		void render();
		void switch_to( const std::string& state_name );
		
	private:

		GameStatePtr m_current_state;

		std::unordered_map< std::string , GameStatePtr > m_state_index;
	
	};

}

#endif