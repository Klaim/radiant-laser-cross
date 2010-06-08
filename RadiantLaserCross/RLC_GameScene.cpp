#include "RLC_GameScene.h"

#include <algorithm>

namespace rlc
{

	GameScene::GameScene()
		: m_need_sort( false )
	{

	}


	void GameScene::add( GameEntity* game_entity )
	{
		GC_ASSERT_NOT_NULL( game_entity );

		if( std::find( m_entities.begin(), m_entities.end(), game_entity ) != m_entities.end() )
		{
			GC_EXCEPTION << "Tried to add the same entity twice in the scene!";
		}

		m_entities.push_back( game_entity );

	}

	void GameScene::remove( GameEntity* game_entity )
	{
		GC_ASSERT_NOT_NULL( game_entity );

		auto found_it = std::find( m_entities.begin(), m_entities.end(), game_entity );

		if( found_it == m_entities.end() )
		{
			GC_EXCEPTION << "Tried to remove an entity not registered in the scene!";
		}

		m_entities.erase( found_it );

	}

	void GameScene::update()
	{
		for( auto it = m_entities.begin(); it != m_entities.end(); ++it )
		{
			GameEntity* game_entity = *it;
			GC_ASSERT_NOT_NULL( game_entity );

			game_entity->update();
		}
	}

	void GameScene::render()
	{
		for( auto it = m_entities.begin(); it != m_entities.end(); ++it )
		{
			GameEntity* game_entity = *it;
			GC_ASSERT_NOT_NULL( game_entity );

			game_entity->render();
		}
	}

}