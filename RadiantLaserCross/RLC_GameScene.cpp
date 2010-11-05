#include "RLC_GameScene.h"

#include <algorithm>

#include "RLC_BulletManager.h"

namespace rlc
{

	GameScene::GameScene()
	{
		BulletManager::create();
	}

	GameScene::~GameScene()
	{
		BulletManager::destroy();
	}


}