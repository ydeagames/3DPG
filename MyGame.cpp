#include "pch.h"
#include "MyGame.h"
#include "GridFloor.h"
#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class GridFloorWrapper : public GameObject
{
	// �O���b�h��
	std::unique_ptr<GridFloor> m_pGridFloor;
	// ����
	void Initialize(GameContext& context)
	{
		// �O���b�h���쐬
		m_pGridFloor = std::make_unique<GridFloor>(context.GetDR().GetD3DDevice(), context.GetDR().GetD3DDeviceContext(), &context.GetStates(), 10.0f, 10);
	}
	// �`��
	void Render(GameContext& context)
	{
		m_pGridFloor->draw(context.GetDR().GetD3DDeviceContext(), context.GetCamera().view, context.GetCamera().projection);
	}
};

class DebugCameraWrapper : public GameObject
{
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_pDebugCamera;
	// ����
	void Initialize(GameContext& context)
	{
		// �O���b�h���쐬
		m_pDebugCamera = std::make_unique<DebugCamera>();
	}
	// �X�V
	void Update(GameContext& context)
	{
		m_pDebugCamera->update();
		context.GetCamera().view = m_pDebugCamera->getViewMatrix();
	}
};

// ����
void MyGame::Initialize(GameContext & context)
{
	// �r���[�s����Z�o����
	SimpleMath::Vector3 eye(0.0f, 0.0f, 10.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	context.GetCamera().view = SimpleMath::Matrix::CreateLookAt(eye, target, up);

	gameObjects.emplace_back(std::unique_ptr<GridFloorWrapper>(new GridFloorWrapper()));
	gameObjects.emplace_back(std::unique_ptr<DebugCameraWrapper>(new DebugCameraWrapper()));

	GameObjectContainer::Initialize(context);
}
