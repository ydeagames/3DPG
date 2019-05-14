#pragma once
#include "StepTimer.h"
#include "GameObjectContainer.h"

// ゲームロジック
class MyGame : public GameObjectContainer
{
public:
	// 生成
	MyGame();
	// 破棄
	~MyGame();
};

