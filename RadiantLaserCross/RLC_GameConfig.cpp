#include "RLC_GameConfig.h"

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>

#include "RLC_Game.h"

namespace rlc
{
	namespace config
	{
		const std::string GAME_TITLE = "Radiant Laser Cross";

		const std::string CONFIG_FILE = "game.cfg";
		
		unsigned int SCREEN_WIDTH = 1024;
		unsigned int SCREEN_HEIGHT = 768;

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
		void read_parameter_force( T& parameter, const std::string& parameter_name, const std::string& info_adress, const ptree& infos )
		{
			auto default_param = parameter;
			auto value = infos.get< ParamType >( info_adress );
			parameter = static_cast< T >( value );
			RLC_LOG << parameter_name << " = " << value << " (default = " << static_cast<ParamType>(default_param) << ")";

		}

		void read_screen_config( const ptree& infos )
		{
			read_parameter( SCREEN_WIDTH, "Screen Width", "screen.width", infos );
			read_parameter( SCREEN_HEIGHT, "Screen Height", "screen.height", infos );

		}

		void read_input_config( const ptree& infos )
		{
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_MOVE_LEFT, "Keyboard : Player ship move left", "input.player.move.left", infos );
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_MOVE_RIGHT, "Keyboard : Player ship move right", "input.player.move.right", infos );
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_MOVE_UP, "Keyboard : Player ship move up", "input.player.move.up", infos );
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_MOVE_DOWN, "Keyboard : Player ship move down", "input.player.move.down", infos );

			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_FIRE_LEFT, "Keyboard : Player ship fire left", "input.player.fire.left", infos );
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_FIRE_RIGHT, "Keyboard : Player ship fire right", "input.player.fire.right", infos );
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_FIRE_UP, "Keyboard : Player ship fire up", "input.player.fire.up", infos );
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_FIRE_DOWN, "Keyboard : Player ship fire down", "input.player.fire.down", infos );

			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_ROTATE_LEFT, "Keyboard : Player ship guns rotate left", "input.player.rotate.left", infos );
			read_parameter_force<char>( KEYBOARD_PLAYERSHIP_ROTATE_RIGHT, "Keyboard : Player ship guns rotate right", "input.player.rotate.right", infos );

		}


	}
	
}