#pragma once
#include "GameObjectContainer.h"

// ゲームロジック
class MyGame : public GameObjectContainer
{
public:
	// 生成
	void Initialize(GameContext& context);
};

