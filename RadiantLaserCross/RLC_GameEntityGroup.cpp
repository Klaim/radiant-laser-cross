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

	void GameEntityGroup::add( GameEntity* game_entity )
	{
		GC_ASSERT_NOT_NULL( game_entity );

		if( std::find( m_entities.begin(), m_entities.end(), game_entity ) != m_entities.end() )
		{
			GC_EXCEPTION << "Tried to add the same entity twice in the scene!";
		}

		m_entities.push_back( game_entity );
		m_need_sort = true;
	}

	void GameEntityGroup::remove( GameEntity* game_entity )
	{
		GC_ASSERT_NOT_NULL( game_entity );

		auto found_it = std::find( m_entities.begin(), m_entities.end(), game_entity );

		if( found_it == m_entities.end() )
		{
			GC_EXCEPTION << "Tried to remove an entity not registered in the scene!";
		}

		m_entities.erase( found_it );

	}

	void GameEntityGroup::update_children()
	{
		Entities entities( m_entities );

		for( auto it = entities.begin(); it != entities.end(); ++it )
		{
			GameEntity* game_entity = *it;
			GC_ASSERT_NOT_NULL( game_entity );

			game_entity->update();
		}
	}

	void GameEntityGroup::render_children()
	{
		Entities entities( m_entities );

		for( auto it = entities.begin(); it != entities.end(); ++it )
		{
			GameEntity* game_entity = *it;
			GC_ASSERT_NOT_NULL( game_entity );

			game_entity->render();
		}
	}

	void GameEntityGroup::sort()
	{
		// TODO : sort by depth
	}

}