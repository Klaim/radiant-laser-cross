#ifndef RLC_GAME_H
#define RLC_GAME_H
#pragma once


#include "GC_LogManager.h"
#include "GC_Log.h"

#include "RLC_GameStateManager.h"

namespace sf
{
	class RenderWindow;
	class Clock;
}

namespace rlc
{
	/** No documentation yet.
	*/
	class Game
	{
	public:

		static Game& current() { GC_ASSERT_NOT_NULL(s_game); return *s_game; }

		Game();
		~Game();

		void run();

		bool is_running() const { return m_running; }
		void exit() { m_running = false; }

		gcore::Log& log() { return *(m_log_manager.getDefaultLog()); }
		gcore::LogManager& log_manager() { return m_log_manager; }
		
		GameStateManager& gamestate_manager() { return m_gamestate_manager; }

		sf::RenderWindow& display() { GC_ASSERT_NOT_NULL( m_window ); return *m_window; }

	private:

		gcore::LogManager m_log_manager;
		GameStateManager m_gamestate_manager;

		sf::RenderWindow* m_window;
		sf::Clock* m_clock;

		float m_last_tick_time;

		bool m_running;
		
				
		void initialize();
		void terminate();

		void update();
		void one_game_tick();
		void render();
				

		Game( const Game& other ); // no copy
		Game& operator=( const Game& other ); // no copy

		// singleton:
		static Game* s_game;

	};

}

#define RLC_LOG rlc::Game::current().log()

#endif