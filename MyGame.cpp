#include "pch.h"
#include "MyGame.h"
#include "GridFloor.h"
#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class GridFloorWrapper : public GameObject
{
	// グリッド床
	std::unique_ptr<GridFloor> m_pGridFloor;
	// 生成
	void Initialize(GameContext& context)
	{
		// グリッド床作成
		m_pGridFloor = std::make_unique<GridFloor>(context.GetDR().GetD3DDevice(), context.GetDR().GetD3DDeviceContext(), &context.GetStates(), 10.0f, 10);
	}
	// 描画
	void Render(GameContext& context)
	{
		m_pGridFloor->draw(context.GetDR().GetD3DDeviceContext(), context.GetCamera().view, context.GetCamera().projection);
	}
};

class DebugCameraWrapper : public GameObject
{
	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_pDebugCamera;
	// 生成
	void Initialize(GameContext& context)
	{
		// グリッド床作成
		m_pDebugCamera = std::make_unique<DebugCamera>();
	}
	// 更新
	void Update(GameContext& context)
	{
		m_pDebugCamera->update();
		context.GetCamera().view = m_pDebugCamera->getViewMatrix();
	}
};

// 生成
void MyGame::Initialize(GameContext & context)
{
	// ビュー行列を算出する
	SimpleMath::Vector3 eye(0.0f, 0.0f, 10.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	context.GetCamera().view = SimpleMath::Matrix::CreateLookAt(eye, target, up);

	gameObjects.emplace_back(std::unique_ptr<GridFloorWrapper>(new GridFloorWrapper()));
	gameObjects.emplace_back(std::unique_ptr<DebugCameraWrapper>(new DebugCameraWrapper()));

	GameObjectContainer::Initialize(context);
}
