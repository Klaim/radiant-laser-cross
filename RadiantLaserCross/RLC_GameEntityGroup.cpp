#include "RLC_GameEntityGroup.h"

#include "RLC_GameEntity.h"

#include <algorithm>

namespace rlc
{
	
	GameEntityGroup::GameEntityGroup()
		: m_need_sort( false )
	{

	}

	GameEntityGroup::~GameEntityGroup()
	{

	}

	void GameEntityGroup::add( GameEntity& game_entity )
	{
		GC_ASSERT_NOT_NULL( &game_entity );

		if( std::find( m_entities.begin(), m_entities.end(), &game_entity ) != m_entities.end() )
		{
			GC_EXCEPTION << "Tried to add the same entity twice in the scene!";
		}

		m_entities.push_back( &game_entity );
		m_need_sort = true;
	}

	void GameEntityGroup::remove( GameEntity& game_entity )
	{
		GC_ASSERT_NOT_NULL( &game_entity );

		auto found_it = std::find( m_entities.begin(), m_entities.end(), &game_entity );

		if( found_it == m_entities.end() )
		{
			GC_EXCEPTION << "Tried to remove an entity not registered in the scene!";
		}

		m_entities.erase( found_it );

	}

	void GameEntityGroup::for_each( const std::function< void( GameEntity& ) >& function )
	{
		Entities entities( m_entities ); // do this on a copy list
		
		std::for_each( entities.begin(), entities.end(), [&function]( GameEntity* game_entity ) // lambda are pure funky awesomeness of everlove
		{
			GC_ASSERT_NOT_NULL( game_entity );
			function( *game_entity );
		});
	}

	void GameEntityGroup::update_children()
	{
		Entities entities( m_entities ); // do this on a copy list
		for_each( []( GameEntity& game_entity ) { game_entity.update(); }); 
	}

	void GameEntityGroup::render_children()
	{
		// make sure entities will be displayed in the plan order
		if( m_need_sort )
			sort();

		for_each( []( GameEntity& game_entity ) { game_entity.render(); });
	}

	void GameEntityGroup::sort()
	{
		// sort by plan depth
		std::sort( m_entities.begin(), m_entities.end(), []( GameEntity* left_entity, GameEntity* right_entity )-> bool
		{
			GC_ASSERT_NOT_NULL( left_entity ); 
			GC_ASSERT_NOT_NULL( right_entity ); 
			return left_entity->plan_idx() < right_entity->plan_idx();
		});
	}

}