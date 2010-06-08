#include "RLC_PlayerShip.h"

#include "sfml/Graphics/Shape.hpp"
#include "sfml/Graphics/Rect.hpp"
#include "sfml/Graphics/RenderWindow.hpp"

#include "RLC_Game.h"
#include "RLC_GameConfig.h"

namespace rlc
{
	

	void PlayerShip::render()
	{
		Position pos = position();
		sf::Vector2f dimensions( 24.0f, 24.0f );
		dimensions += pos;

		sf::Shape ship_shape = sf::Shape::Rectangle( pos, dimensions , sf::Color( 0, 255, 0 ) );
		
		Game::current().display().Draw( ship_shape );
		
	}

	void PlayerShip::update()
	{
		using namespace sf;

		const Input& input = Game::current().display().GetInput();

		Position move;
		Position position = this->position();

		// TODO : rewrite all this!

		if( input.IsKeyDown( Key::Left ) )
		{
			if( position.x > 0 )
				move.x -= 1;
		}

		if( input.IsKeyDown( Key::Right ) )
		{
			if( position.x < ( SCREEN_WIDTH - 24.0f ) ) 
				move.x += 1;
		}

		if( input.IsKeyDown( Key::Up ) )
		{
			if( position.y > 0 )
				move.y -= 1;
		}

		if( input.IsKeyDown( Key::Down ) )
		{
			if( position.y < ( SCREEN_HEIGHT - 24.0f ) )
				move.y += 1;
		}

		move *= PLAYER_SHIP_SPEED;
		position += move;
		this->position( position );
	}

}