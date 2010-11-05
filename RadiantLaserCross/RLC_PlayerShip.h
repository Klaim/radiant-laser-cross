#ifndef RLC_PLAYERSHIP_H
#define RLC_PLAYERSHIP_H
#pragma once

#include <array>

#include "RLC_Ship.h"
#include "RLC_Gun.h"

namespace rlc
{
	namespace config
	{
		const unsigned int MAX_PLAYER_GUNS = 4;
	}

	enum GunsSetup
	{
		GunsSetup_East = 0,
		GunsSetup_North,
		GunsSetup_West,
		GunsSetup_South,
	};
	
	/** No documentation yet.
	*/
	class PlayerShip
		: public Ship< config::MAX_PLAYER_GUNS >
	{
	public:

		PlayerShip();
		
	private:

		GunsSetup m_guns_setup;
		Orientation m_guns_orientation;
		
		void do_render();
		void do_update();

		void update_move();
		void update_guns();

		void render_ship();
		void render_guns();
		void render_gun( unsigned int gun_idx );

		int gun_id( unsigned int slot );

		Orientation gun_direction( unsigned int gun_idx ) const;
		Orientation slot_direction( unsigned int gun_idx ) const;
		sf::Color gun_color( unsigned int gun_idx ) const;

		void rotate_guns( int setups );
		bool is_rotating_guns() const;

		void fire( GunsSetup dir );
	};
	
}

#endif