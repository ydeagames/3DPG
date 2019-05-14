#pragma once
#include "StepTimer.h"
#include "DeviceResources.h"
#include <SimpleMath.h>

// カメラ取得
class GameCamera
{
public:
	// ビュー行列
	DirectX::SimpleMath::Matrix view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix projection;
};

// GameContextインターフェイス
// 今回はVC++固有仕様の__interfaceを使ってみた。(学校としてどうなのかは不明)
__interface GameContext
{
public:
	// DeviceResource取得
	DX::DeviceResources& GetDR();
	// タイマー取得
	DX::StepTimer& GetTimer();
	// カメラ取得
	GameCamera& GetCamera();
};

