#pragma once
#include "StepTimer.h"

// ゲームオブジェクト
class GameObject
{
public:
	// 生成
	GameObject() = default;
	// 更新
	virtual void Update(DX::StepTimer const& timer) {};
	// 描画
	virtual void Render() {};
	// 破棄
	virtual ~GameObject() = default;
};

