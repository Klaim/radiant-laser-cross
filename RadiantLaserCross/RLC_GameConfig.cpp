#include "RLC_GameConfig.h"

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>

#include "RLC_Game.h"

namespace rlc
{
	// TODO : make it two singleton classes : one with user-defined config (can change) and one for gameplay config (with read-only access).
	namespace config
	{
		const std::string GAME_TITLE = "Radiant Laser Cross";

		const std::string CONFIG_FILE = "game.cfg";
		
		const unsigned int SCREEN_WIDTH = 1024;
		const unsigned int SCREEN_HEIGHT = 768;

		unsigned int GAME_SCENE_WIDTH = 600;
		unsigned int GAME_SCENE_HEIGHT = SCREEN_HEIGHT;


		const float TICK_TIME = 1.0f / 60.0f;

		float PLAYER_SHIP_SPEED = 5.0f;

		

		int KEYBOARD_PLAYERSHIP_MOVE_LEFT		= 'j';
		int KEYBOARD_PLAYERSHIP_MOVE_RIGHT		= 'l';
		int KEYBOARD_PLAYERSHIP_MOVE_UP			= 'i';
		int KEYBOARD_PLAYERSHIP_MOVE_DOWN		= 'k';

		int KEYBOARD_PLAYERSHIP_FIRE_LEFT		= 'j';
		int KEYBOARD_PLAYERSHIP_FIRE_RIGHT		= 'l';
		int KEYBOARD_PLAYERSHIP_FIRE_UP			= 'i';
		int KEYBOARD_PLAYERSHIP_FIRE_DOWN		= 'k';

		int KEYBOARD_PLAYERSHIP_ROTATE_RIGHT	= 'o';
		int KEYBOARD_PLAYERSHIP_ROTATE_LEFT		= 'u';

		int JOYSTICK_PLAYERSHIP_FIRE_LEFT		= 2;
		int JOYSTICK_PLAYERSHIP_FIRE_RIGHT		= 1;
		int JOYSTICK_PLAYERSHIP_FIRE_UP			= 0;
		int JOYSTICK_PLAYERSHIP_FIRE_DOWN		= 3;

		int JOYSTICK_PLAYERSHIP_ROTATE_RIGHT	= 4;
		int JOYSTICK_PLAYERSHIP_ROTATE_LEFT		= 5;

		int JOYSTICK_PLAYERSHIP_ROTATE_AXIS		= -1;
		int JOYSTICK_PLAYERSHIP_FIRE_AXIS_X		= -1;
		int JOYSTICK_PLAYERSHIP_FIRE_AXIS_Y		= -1;



		using namespace boost::property_tree;

		void read_screen_config( const ptree& infos );
		void read_input_config( const ptree& infos );

		void load_config()
		{
			using namespace boost;
			RLC_LOG << "Reading config file : " << CONFIG_FILE;

			if( filesystem::exists( CONFIG_FILE ) )
			{
				RLC_LOG << "The file exists, reading...";

				ptree config_info;
				read_info( CONFIG_FILE, config_info );
				
				read_screen_config( config_info );
				read_input_config( config_info );

				RLC_LOG << "Closing config file.";
			}
			else
			{
				RLC_LOG << "Config file not found, will use default settings!";

			}

		}

		template < typename T >
		void read_parameter( T& parameter, const std::string& parameter_name, const std::string& info_adress, const ptree& infos )
		{
			auto default_param = parameter;
			parameter = infos.get< T >( info_adress, parameter );
			RLC_LOG << parameter_name << " = " << parameter << " (default = " << default_param << ")";

		}

		template < typename ParamType, typename T >
		void read_parameter_cast( T& parameter, const std::string& parameter_name, const std::string& info_adress, const ptree& infos )
		{
			auto default_param = parameter;
			auto value = infos.get< ParamType >( info_adress );
			parameter = static_cast< T >( value );
			RLC_LOG << parameter_name << " = " << value << " (default = " << static_cast<ParamType>(default_param) << ")";

		}

		void read_screen_config( const ptree& infos )
		{
		
		}

		void read_input_config( const ptree& infos )
		{
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_MOVE_LEFT, "Keyboard : Player ship move left", "input.keyboard.move.left", infos );
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_MOVE_RIGHT, "Keyboard : Player ship move right", "input.keyboard.move.right", infos );
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_MOVE_UP, "Keyboard : Player ship move up", "input.keyboard.move.up", infos );
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_MOVE_DOWN, "Keyboard : Player ship move down", "input.keyboard.move.down", infos );

			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_FIRE_LEFT, "Keyboard : Player ship fire left", "input.keyboard.fire.left", infos );
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_FIRE_RIGHT, "Keyboard : Player ship fire right", "input.keyboard.fire.right", infos );
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_FIRE_UP, "Keyboard : Player ship fire up", "input.keyboard.fire.up", infos );
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_FIRE_DOWN, "Keyboard : Player ship fire down", "input.keyboard.fire.down", infos );

			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_ROTATE_LEFT, "Keyboard : Player ship guns rotate left", "input.keyboard.rotate.left", infos );
			read_parameter_cast<char>( KEYBOARD_PLAYERSHIP_ROTATE_RIGHT, "Keyboard : Player ship guns rotate right", "input.keyboard.rotate.right", infos );

			read_parameter( JOYSTICK_PLAYERSHIP_FIRE_LEFT, "Joystick : Player ship fire left", "input.joystick.fire.left", infos );
			read_parameter( JOYSTICK_PLAYERSHIP_FIRE_RIGHT, "Joystick : Player ship fire right", "input.joystick.fire.right", infos );
			read_parameter( JOYSTICK_PLAYERSHIP_FIRE_UP, "Joystick : Player ship fire up", "input.joystick.fire.up", infos );
			read_parameter( JOYSTICK_PLAYERSHIP_FIRE_DOWN, "Joystick : Player ship fire down", "input.joystick.fire.down", infos );

			read_parameter( JOYSTICK_PLAYERSHIP_ROTATE_LEFT, "Joystick : Player ship guns rotate left", "input.joystick.rotate.left", infos );
			read_parameter( JOYSTICK_PLAYERSHIP_ROTATE_RIGHT, "Joystick : Player ship guns rotate right", "input.joystick.rotate.right", infos );

			read_parameter( JOYSTICK_PLAYERSHIP_ROTATE_AXIS, "Joystick : Player ship guns rotate axis", "input.joystick.rotate.axis", infos );
			read_parameter( JOYSTICK_PLAYERSHIP_FIRE_AXIS_X, "Joystick : Player ship guns rotate axis", "input.joystick.fire.axis_x", infos );
			read_parameter( JOYSTICK_PLAYERSHIP_FIRE_AXIS_Y, "Joystick : Player ship guns rotate axis", "input.joystick.fire.axis_y", infos );

		}


	}
	
}