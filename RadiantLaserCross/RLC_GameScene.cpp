#include "RLC_GameScene.h"

#include <algorithm>

#include "RLC_BulletManager.h"

namespace rlc
{

	GameScene::GameScene()
	{
		BulletManager::create();
		BulletManager::instance().reset( 200 );
	}

	GameScene::~GameScene()
	{
		BulletManager::destroy();
	}


}