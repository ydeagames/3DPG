#pragma once
#include "StepTimer.h"
#include "GameObject.h"

// ゲームオブジェクトコンテナ
class GameObjectContainer : public GameObject
{
public:
	// 子ゲームオブジェクト
	std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
	// 更新
	void Update(DX::StepTimer const& timer);
	// 描画
	void Render();
};