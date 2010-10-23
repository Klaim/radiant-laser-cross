#include "RLC_Game.h"

#include <boost/make_shared.hpp>

#include "sfml/System.hpp"
#include "sfml/Window.hpp"
#include "sfml/Graphics.hpp"
#include "sfml/Audio.hpp"

#include "RLC_GameConfig.h"
#include "RLC_GameStateNames.h"
#include "RLC_GameSession.h"



namespace rlc
{
	
	Game::Game()
		: m_running( false )
		, m_window( nullptr )
		, m_clock( nullptr )
		, m_last_tick_time( 0.0f )
	{
		
	}

	Game::~Game()
	{
		
	}

	void Game::run()
	{
		RLC_LOG << "Starting " << GAME_TITLE ;

		initialize();

		GC_ASSERT_NOT_NULL( m_window );
		m_running = true;

		while( is_running() && m_window->IsOpened() )
		{
			update();
			render();
		}

		terminate();
	}

	void Game::initialize()
	{
		RLC_LOG << "Initialization...";

		// first create the window
		GC_ASSERT_NULL( m_window );
		m_window = new sf::RenderWindow( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close );
		
		GC_ASSERT_NULL( m_clock );
		m_clock = new sf::Clock();

		// now create the states
		m_gamestate_manager.add( boost::make_shared<GameSession>() );
		
		// begin the first state
		m_gamestate_manager.switch_to( GAMESTATE_GAME_SESSION );

		RLC_LOG << "Initialization done.";
	}


	void Game::terminate()
	{
		RLC_LOG << "Termination...";

		delete m_clock;
		m_clock = nullptr;

		delete m_window;
		m_window = nullptr;

		RLC_LOG << "Terminated!";
	}


	void Game::update()
	{
		GC_ASSERT_NOT_NULL( m_window );
		GC_ASSERT_NOT_NULL( m_clock );

		// process window events
		sf::Event Event;
		while ( m_window->GetEvent(Event) )
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				m_window->Close();
		}

		// perform each tick that passed since last tick!

		const float time_since_start = m_clock->GetElapsedTime();
		float time_since_last_tick = time_since_start - m_last_tick_time;

		while( time_since_last_tick > TICK_TIME )
		{
			m_last_tick_time = time_since_start;
			time_since_last_tick -= TICK_TIME;

			one_game_tick();
		}

	}

	void Game::one_game_tick()
	{
		GC_ASSERT_NOT_NULL( m_window );
		GC_ASSERT_NOT_NULL( m_clock );

		m_gamestate_manager.update();
		
	}

	void Game::render()
	{
		GC_ASSERT_NOT_NULL( m_window );

		// graphic rendering

		m_window->Clear( sf::Color( 0, 0, 80, 0 ) );

		m_gamestate_manager.render();

		m_window->Display();

		// audio rendering

		// TODO : add audio update here
	}


}