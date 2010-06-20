#include "RLC_GameConfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

namespace rlc
{
	const unsigned int SCREEN_WIDTH = 1024;
	const unsigned int SCREEN_HEIGHT = 768;

	const unsigned int GAME_SCENE_WIDTH = 600;
	const unsigned int GAME_SCENE_HEIGHT = SCREEN_HEIGHT;

	const std::string GAME_TITLE = "Radiant Laser Cross";

	const float TICK_TIME = 1.0f / 60.0f;

	const float PLAYER_SHIP_SPEED = 5.0f;

	const std::string CONFIG_FILE = "game.cfg";

	void read_config()
	{
		/*using namespace boost::property_tree;
		ptree properties;

		read_info( CONFIG_FILE, properties );
		*/
	}
}