#ifndef RLC_GAME_H
#define RLC_GAME_H
#pragma once

#include <boost/scoped_ptr.hpp>

#include "GC_LogManager.h"
#include "GC_Log.h"
#include "GC_Singleton.h"

#include "RLC_GameStateManager.h"

namespace sf
{
	class RenderWindow;
}

namespace rlc
{
	/** The game object representing the whole game.
	*/
	class Game : public gcore::Singleton< Game >
	{
	public:

		void run();


		bool is_running() const { return m_running; }
		void exit() { m_running = false; }

		gcore::Log& log() { return *(m_log_manager.getDefaultLog()); }
		gcore::LogManager& log_manager() { return m_log_manager; }
		
		GameStateManager& gamestate_manager() { return m_gamestate_manager; }

		sf::RenderWindow& display();

	private:

		friend class gcore::Singleton < Game >;
		Game();
		~Game();


		gcore::LogManager m_log_manager;
		GameStateManager m_gamestate_manager;

		class System;
		boost::scoped_ptr< System > m_system;
		
		float m_last_tick_time;

		bool m_running;
		
				
		void initialize();
		void terminate();

		void update();
		void one_game_tick();
		void render();
		
	};

}

#define RLC_LOG rlc::Game::instance().log()

#endif