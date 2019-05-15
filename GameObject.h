#pragma once
#include "GameContext.h"
#include "Transform.h"

// ゲームオブジェクト
class GameObject
{
public:
	Transform transform;

public:
	GameObject() = default;
	virtual ~GameObject() = default;

public:
	// 生成
	virtual void Initialize(GameContext& context) {};
	// 更新
	virtual void Update(GameContext& context) {};
	// 描画
	virtual void Render(GameContext& context) {};
	// 破棄
	virtual void Finalize(GameContext& context) {};
};

