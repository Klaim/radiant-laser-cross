#include "RLC_GameSession.h"

#include "sfml/Graphics/RenderWindow.hpp"

#include "RLC_GameStateNames.h"
#include "RLC_Game.h"



namespace rlc
{

	GameSession::GameSession()
		: GameState( names::GAMESTATE_GAME_SESSION )
	{

	}



	void GameSession::begin()
	{
		m_scene.add( &m_player.ship() );
	}

	void GameSession::end()
	{
		m_scene.remove( &m_player.ship() );
	}


	void GameSession::update()
	{
		if( Game::instance().display().GetInput().IsKeyDown( sf::Key::Escape ) )
		{
			Game::instance().exit();
			return;
		}

		m_scene.update();
	}


	void GameSession::render()
	{
		m_scene.render();
	}


	
}