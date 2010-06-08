#include "RLC_PlayerShip.h"

#include "sfml/Graphics/Shape.hpp"
#include "sfml/Graphics/Rect.hpp"
#include "sfml/Graphics/RenderWindow.hpp"

#include "RLC_Game.h"
#include "RLC_GameConfig.h"

namespace rlc
{
	const float SHIP_WIDTH = 32.0f;
	const float SHIP_HEIGHT = 32.0f;


	PlayerShip::PlayerShip()
	{
		box( Box(-4,-4,4,4) );
		position( Position( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ) ) ;
	}


	void PlayerShip::do_render()
	{
		Position pos = position();
		
		const float ship_center_x = SHIP_WIDTH/2;
		const float ship_center_y = SHIP_HEIGHT/2;

		sf::Vector2f top_left( -ship_center_x, -ship_center_y );
		sf::Vector2f bottom_right( ship_center_x, ship_center_y );
		
		top_left += pos;
		bottom_right += pos;

		sf::Shape ship_shape = sf::Shape::Rectangle( top_left, bottom_right , sf::Color( 0, 180, 30 ) );
		
		Game::current().display().Draw( ship_shape );
		Game::current().display().Draw( shape() );
	}

	void PlayerShip::do_update()
	{
		update_move();
	}

	void PlayerShip::update_move()
	{
		using namespace sf;

		const Input& input = Game::current().display().GetInput();

		Position move;
		Position position = this->position();

		// TODO : rewrite all this!

		static const float JOYSTICK_TOLERANCE = 1.0f;

		if( input.IsKeyDown( Key::Left ) || input.GetJoystickAxis(0, sf::Joy::AxisX ) < -JOYSTICK_TOLERANCE )
		{
			if( position.x > SHIP_WIDTH/2 )
				move.x -= 1;
		}

		if( input.IsKeyDown( Key::Right ) || input.GetJoystickAxis(0, sf::Joy::AxisX ) > JOYSTICK_TOLERANCE )
		{
			if( position.x < ( SCREEN_WIDTH - (SHIP_WIDTH/2) ) ) 
				move.x += 1;
		}

		if( input.IsKeyDown( Key::Up ) || input.GetJoystickAxis(0, sf::Joy::AxisY ) < -JOYSTICK_TOLERANCE )
		{
			if( position.y > SHIP_HEIGHT/2 )
				move.y -= 1;
		}

		if( input.IsKeyDown( Key::Down ) || input.GetJoystickAxis(0, sf::Joy::AxisY ) > JOYSTICK_TOLERANCE )
		{
			if( position.y < ( SCREEN_HEIGHT - (SHIP_HEIGHT/2) ) )
				move.y += 1;
		}

		move *= PLAYER_SHIP_SPEED;
		position += move;
		this->position( position );
	}

}