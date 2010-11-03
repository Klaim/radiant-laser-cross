#ifndef RLC_GAMECONFIG_H
#define RLC_GAMECONFIG_H
#pragma once

#include <string>

namespace rlc
{
	namespace config
	{

		extern const unsigned int SCREEN_WIDTH;
		extern const unsigned int SCREEN_HEIGHT;

		extern unsigned int GAME_SCENE_WIDTH;
		extern unsigned int GAME_SCENE_HEIGHT;

		extern const std::string GAME_TITLE;

		extern const float TICK_TIME;

		extern float PLAYER_SHIP_SPEED;

		
		extern int KEYBOARD_PLAYERSHIP_MOVE_LEFT;
		extern int KEYBOARD_PLAYERSHIP_MOVE_RIGHT;
		extern int KEYBOARD_PLAYERSHIP_MOVE_UP;
		extern int KEYBOARD_PLAYERSHIP_MOVE_DOWN;

		extern int KEYBOARD_PLAYERSHIP_FIRE_LEFT;
		extern int KEYBOARD_PLAYERSHIP_FIRE_RIGHT;
		extern int KEYBOARD_PLAYERSHIP_FIRE_UP;
		extern int KEYBOARD_PLAYERSHIP_FIRE_DOWN;

		extern int KEYBOARD_PLAYERSHIP_ROTATE_LEFT;
		extern int KEYBOARD_PLAYERSHIP_ROTATE_RIGHT;

		extern int JOYSTICK_PLAYERSHIP_FIRE_LEFT;
		extern int JOYSTICK_PLAYERSHIP_FIRE_RIGHT;
		extern int JOYSTICK_PLAYERSHIP_FIRE_UP;
		extern int JOYSTICK_PLAYERSHIP_FIRE_DOWN;

		extern int JOYSTICK_PLAYERSHIP_ROTATE_LEFT;
		extern int JOYSTICK_PLAYERSHIP_ROTATE_RIGHT;

		/** Load the config file if it exists and extract all configuration informations it can find in it.
			The config file is assumed to be written in the INFO format.
		*/
		void load_config();

	}


}

#endif