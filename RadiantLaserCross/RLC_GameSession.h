#ifndef RLC_GAMESESSION_H
#define RLC_GAMESESSION_H
#pragma once

#include "RLC_GameState.h"
#include "RLC_GameScene.h"
#include "RLC_Player.h"

namespace rlc
{
	/** No documentation yet.
	*/
	class GameSession 
		: public GameState
	{
	public:

		GameSession();
		
		void begin(); 
		void update();
		void render();
		void end();
		

	private:

		GameScene m_scene;
		Player m_player;
	
	};
	
}

#endif