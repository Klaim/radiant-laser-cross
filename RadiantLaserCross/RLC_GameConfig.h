#ifndef RLC_GAMECONFIG_H
#define RLC_GAMECONFIG_H
#pragma once

#include <string>

namespace rlc
{
	// hardcoded configuration
	// TODO : fill from config file

	const unsigned int SCREEN_WIDTH = 1024;
	const unsigned int SCREEN_HEIGHT = 768;

	const unsigned int GAME_SCENE_WIDTH = 600;
	const unsigned int GAME_SCENE_HEIGHT = SCREEN_HEIGHT;

	const std::string GAME_TITLE = "Radiant Laser Cross";

	const float TICK_TIME = 1.0f / 60.0f;

	const float PLAYER_SHIP_SPEED = 4.0f;

}

#endif