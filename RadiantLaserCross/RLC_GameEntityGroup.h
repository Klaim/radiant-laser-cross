#ifndef RLC_GAMEENTITYGROUP_H
#define RLC_GAMEENTITYGROUP_H
#pragma once

#include <vector>


namespace rlc
{
	class GameEntity;

	/** No documentation yet.
	*/
	class GameEntityGroup
	{
	public:

		GameEntityGroup();
		~GameEntityGroup();
		
		void add( GameEntity* game_entity );
		void remove( GameEntity* game_entity );
	
	protected:	
		void update_children();
		void render_children();

	private:

		typedef std::vector< GameEntity* > Entities;
		Entities m_entities;

		bool m_need_sort;		

		void sort();
	
	};
	
}

#endif