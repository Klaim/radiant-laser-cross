#ifndef RLC_GAMEENTITYGROUP_H
#define RLC_GAMEENTITYGROUP_H
#pragma once

#include <vector>
#include <functional>


namespace rlc
{
	class GameEntity;

	/** Group of game entities that can be updated and rendered together.
	*/
	class GameEntityGroup
	{
	public:

		typedef std::vector< GameEntity* > Entities;

		GameEntityGroup();
		~GameEntityGroup();
		
		void add( GameEntity& game_entity );
		void remove( GameEntity& game_entity );
	
	protected:	
		
		void for_each( const std::function< void( GameEntity& ) >& function );

		void update_children();
		void render_children();

		const Entities& children() const { return m_entities;}

	private:

		
		Entities m_entities;

		bool m_need_sort;		

		void sort();
		
	
	};
	
}

#endif