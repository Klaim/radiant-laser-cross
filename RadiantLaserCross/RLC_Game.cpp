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
	using namespace config;

	class Game::System : boost::noncopyable
	{
	public:

		sf::RenderWindow& window() { return m_window; }
		sf::Clock& clock() { return m_clock; }

		System()
			: m_window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close )
			, m_clock()
		{}

	private:

		sf::RenderWindow m_window;
		sf::Clock m_clock;

	};
	
	Game::Game()
		: m_running( false )
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

		m_running = true;

		while( is_running() && display().IsOpened() )
		{
			update();
			render();
		}

		terminate();
	}

	void Game::initialize()
	{
		RLC_LOG << "Initialization...";

		load_config();

		// first create the system resources
		m_system.reset( new System() );

		// now create the states
		m_gamestate_manager.add( boost::make_shared<GameSession>() );
		
		// begin the first state
		m_gamestate_manager.switch_to( names::GAMESTATE_GAME_SESSION );

		RLC_LOG << "Initialization done.";
	}


	void Game::terminate()
	{
		RLC_LOG << "Termination...";

		m_system.reset();
		
		RLC_LOG << "Terminated!";
	}


	void Game::update()
	{
		GC_ASSERT_NOT_NULL( m_system );

		// process window events
		sf::Event Event;
		auto& window = display();
		while ( window.GetEvent(Event) )
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				window.Close();
		}

		// perform each tick that passed since last tick!
		const float time_since_start = m_system->clock().GetElapsedTime();
		float time_since_last_tick = time_since_start - m_last_tick_time;

		while( time_since_last_tick > config::TICK_TIME )
		{
			m_last_tick_time = time_since_start;
			time_since_last_tick -= config::TICK_TIME;

			one_game_tick();
		}

	}

	void Game::one_game_tick()
	{
		GC_ASSERT_NOT_NULL( m_system );

		m_gamestate_manager.update();
		
	}

	void Game::render()
	{
		GC_ASSERT_NOT_NULL( m_system );

		// graphic rendering

		auto& window = display();
		window.Clear( sf::Color( 0, 0, 80, 0 ) );

		m_gamestate_manager.render();

		window.Display();

		// audio rendering

		// TODO : add audio update here
	}

	sf::RenderWindow& Game::display()
	{
		GC_ASSERT_NOT_NULL( m_system ); 
		return m_system->window();
	}


}