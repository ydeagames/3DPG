#include "pch.h"
#include "MyGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 生成
void MyGame::Initialize(GameContext & context)
{
	// ビュー行列を算出する
	SimpleMath::Vector3 eye(0.0f, 0.0f, 10.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	context.GetCamera().view = SimpleMath::Matrix::CreateLookAt(eye, target, up);

	GameObjectContainer::Initialize(context);

	class ObjA : public GameObject
	{

		// 生成
		void Initialize(GameContext& context)
		{

		}
		// 更新
		void Update(GameContext& context)
		{

		}
		// 描画
		void Render(GameContext& context)
		{

		}
		// 破棄
		void Finalize(GameContext& context)
		{

		}
	};
}
