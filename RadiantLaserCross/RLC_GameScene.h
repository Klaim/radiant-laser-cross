#ifndef RLC_GAMESCENE_H
#define RLC_GAMESCENE_H
#pragma once

#include <vector>

#include "GC_Singleton.h"
#include "RLC_GameEntity.h"
#include "RLC_GameEntityGroup.h"

namespace rlc
{
	/** No documentation yet.
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