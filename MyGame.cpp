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

class ModelObject : public GameObject
{
	// 名前
	std::wstring m_name;
	// モデル
	std::unique_ptr<Model> m_model;
public:
	// コンストラクタ
	ModelObject(const std::wstring& name)
		: m_name(name)
	{
	}
	// 生成
	void Initialize(GameContext& context)
	{
		// モデル作成
		m_model = DirectX::Model::CreateFromCMO(context.GetDR().GetD3DDevice(), m_name.c_str(), context.GetEffectFactory());

		// エフェクトを更新する
		m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ライトの設定
			DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightingEnabled(true);
				lights->SetPerPixelLighting(true);
				lights->SetLightEnabled(0, true);
				lights->SetLightDiffuseColor(0, DirectX::Colors::AntiqueWhite);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}

			// きりの設定 (いらない)
			/*
			DirectX::IEffectFog* fog = dynamic_cast<DirectX::IEffectFog*>(effect);
			if (fog)
			{
			fog->SetFogEnabled(true);
			fog->SetFogColor(DirectX::Colors::CornflowerBlue);
			fog->SetFogStart(50.f);
			fog->SetFogEnd(60.f);
			}
			*/
		});
	}
	// 描画
	void Render(GameContext& context)
	{
		// モデルを描画する
		m_model->Draw(context.GetDR().GetD3DDeviceContext(), context.GetStates(), transform.GetMMatrix(), context.GetCamera().view, context.GetCamera().projection);
	}
};

class ModelObjectControl : public ModelObject
{
public:
	// コンストラクタ
	ModelObjectControl(const std::wstring& name)
		: ModelObject(name)
	{
	}
	// 更新
	void Update(GameContext& context)
	{
		auto kb = Keyboard::Get().GetState();
		if (kb.A)
			transform.SetPosition(transform.GetPosition() + Vector3::Left);
		if (kb.D)
			transform.SetPosition(transform.GetPosition() + Vector3::Right);
		if (kb.W)
			transform.SetPosition(transform.GetPosition() + Vector3::Forward);
		if (kb.S)
			transform.SetPosition(transform.GetPosition() + Vector3::Backward);
	};
};

// 生成
void MyGame::Initialize(GameContext & context)
{
	// ビュー行列を算出する
	SimpleMath::Vector3 eye(0.0f, 0.0f, 10.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	context.GetCamera().view = SimpleMath::Matrix::CreateLookAt(eye, target, up);

	gameObjects.emplace_back(std::move(std::unique_ptr<GridFloorWrapper>(new GridFloorWrapper())));
	gameObjects.emplace_back(std::move(std::unique_ptr<DebugCameraWrapper>(new DebugCameraWrapper())));
	gameObjects.emplace_back(std::move(std::unique_ptr<ModelObjectControl>(new ModelObjectControl(L"Resources/Models/plane.cmo"))));
	gameObjects.emplace_back(std::move(std::unique_ptr<ModelObject>(new ModelObject(L"Resources/Models/skydoom.cmo"))));
	gameObjects.emplace_back(std::move(std::unique_ptr<ModelObject>(new ModelObject(L"Resources/Models/floor.cmo"))));

	GameObjectContainer::Initialize(context);
}
