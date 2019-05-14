#pragma once
#include "GameObject.h"

// ゲームオブジェクトコンテナ
class GameObjectContainer : public GameObject
{
public:
	// 子ゲームオブジェクト
	std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
	// 描画
	void Render(GameContext& context);
	// 破棄
	void Finalize(GameContext& context);
};