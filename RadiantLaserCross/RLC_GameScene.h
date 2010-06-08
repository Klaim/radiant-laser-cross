#ifndef RLC_GAMESCENE_H
#define RLC_GAMESCENE_H
#pragma once

#include <vector>

#include "RLC_GameEntity.h"

namespace rlc
{
	/** No documentation yet.
	*/
	class GameScene
	{
	public:
		GameScene();

		void add( GameEntity* game_entity );
		void remove( GameEntity* game_entity );

		void update();
		void render();
		
	private:

		bool m_need_sort;
		std::vector< GameEntity* > m_entities;
	
		void sort();
	};

	

}

#endif