#include "pch.h"
#include "MyGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// ����
void MyGame::Initialize(GameContext & context)
{
	// �r���[�s����Z�o����
	SimpleMath::Vector3 eye(0.0f, 0.0f, 10.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	context.GetCamera().view = SimpleMath::Matrix::CreateLookAt(eye, target, up);

	GameObjectContainer::Initialize(context);

	class ObjA : public GameObject
	{

		// ����
		void Initialize(GameContext& context)
		{

		}
		// �X�V
		void Update(GameContext& context)
		{

		}
		// �`��
		void Render(GameContext& context)
		{

		}
		// �j��
		void Finalize(GameContext& context)
		{

		}
	};
}
