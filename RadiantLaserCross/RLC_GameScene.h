#ifndef RLC_GAMESCENE_H
#define RLC_GAMESCENE_H
#pragma once

#include <vector>

#include "GC_Singleton.h"
#include "RLC_GameEntity.h"
#include "RLC_GameEntityGroup.h"

namespace rlc
{
	/** The scene contains all the visible elements of the game at any time.
		To make sure elements are updated and rendered, add them to this object.
	*/
	class GameScene 
		: public gcore::Singleton< GameScene >
		, public GameEntityGroup
	{
	public:
		GameScene();
		~GameScene();

		void update() { update_children(); }
		void render() { render_children(); }
	};

	

}

#endif