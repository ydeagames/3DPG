#include "pch.h"
#include "MyGame.h"
#include "GridFloor.h"
#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �O���b�h��
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

// �f�o�b�O�J����
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

// ���f��
class ModelObject : public GameObject
{
	// ���O
	std::wstring m_name;
	// ���f��
	std::unique_ptr<Model> m_model;
public:
	// �R���X�g���N�^
	ModelObject(const std::wstring& name)
		: m_name(name)
	{
	}
	// ����
	void Initialize(GameContext& context)
	{
		// ���f���쐬
		m_model = DirectX::Model::CreateFromCMO(context.GetDR().GetD3DDevice(), m_name.c_str(), context.GetEffectFactory());

		// �G�t�F�N�g���X�V����
		m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ���C�g�̐ݒ�
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

			// ����̐ݒ� (����Ȃ�)
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
	// �`��
	void Render(GameContext& context)
	{
		// ���f����`�悷��
		m_model->Draw(
			context.GetDR().GetD3DDeviceContext(),
			context.GetStates(), transform.GetMMatrix(),
			context.GetCamera().view,
			context.GetCamera().projection,
			false,
			[&]() { context.GetDR().GetD3DDeviceContext()->OMSetBlendState(context.GetStates().AlphaBlend(), Colors::Black, 0xFFFFFFFF); });
	}
};

// �v���~�e�B�u
class GeometricObject : public GameObject
{
	// �W�I���g���v���~�e�B�u
	std::function<std::unique_ptr<DirectX::GeometricPrimitive>(GameContext& context)> m_geometricPrimitiveGenerator;
	// �W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	// �F
	Color m_color;

public:
	// �R���X�g���N�^
	GeometricObject(const std::function<std::unique_ptr<DirectX::GeometricPrimitive>(GameContext& context)>& generator, Color color = Color(DirectX::Colors::Gray))
		: m_geometricPrimitiveGenerator(generator)
		, m_color(color)
	{
	}
	// ����
	void Initialize(GameContext& context)
	{
		// �W�I���g���쐬
		m_pGeometricPrimitive = m_geometricPrimitiveGenerator(context);
	}
	// �`��
	void Render(GameContext& context)
	{
		// �W�I���g���`��
		m_pGeometricPrimitive->Draw(transform.GetMMatrix(), context.GetCamera().view, context.GetCamera().projection, m_color);
	}
};

// ���f���R���g���[��
class ModelObjectControl : public ModelObject
{
public:
	// �R���X�g���N�^
	ModelObjectControl(const std::wstring& name)
		: ModelObject(name)
	{
	}
	// �X�V
	void Update(GameContext& context)
	{
		auto kb = Keyboard::Get().GetState();
		float speed = -.1f;
		if (kb.A)
			transform.SetPosition(transform.GetPosition() + Vector3::Left * speed);
		if (kb.D)
			transform.SetPosition(transform.GetPosition() + Vector3::Right * speed);
		if (kb.W)
			transform.SetPosition(transform.GetPosition() + Vector3::Forward * speed);
		if (kb.S)
			transform.SetPosition(transform.GetPosition() + Vector3::Backward * speed);
	};
};

// �r�b�g
class BitObject : public GeometricObject
{
	Transform* m_base;

public:
	BitObject(const std::function<std::unique_ptr<DirectX::GeometricPrimitive>(GameContext& context)>& generator, Color color, Transform* base)
		: GeometricObject(generator, color)
		, m_base(base)
	{
	}
	// �X�V
	void Update(GameContext& context)
	{
		float time = static_cast<float>(context.GetTimer().GetTotalSeconds());
		transform.LocalEulerAngles.z = time;
		transform.LocalPosition = Vector3::Transform(Vector3::Down, Matrix::CreateTranslation(Vector3::Down * .8f) * Matrix::CreateRotationZ(time));
	}
};

// ����
void MyGame::Initialize(GameContext & context)
{
	// �����̃r���[�s����Z�o����
	SimpleMath::Vector3 eye(0.0f, 0.0f, 10.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	context.GetCamera().view = SimpleMath::Matrix::CreateLookAt(eye, target, up);

	// �O���b�h�t���A
	//gameObjects.emplace_back(std::move(std::unique_ptr<GridFloorWrapper>(new GridFloorWrapper())));
	// �f�o�b�O�J����
	gameObjects.emplace_back(std::move(std::unique_ptr<DebugCameraWrapper>(new DebugCameraWrapper())));
	// �V��
	gameObjects.emplace_back(std::move(std::unique_ptr<ModelObject>(new ModelObject(L"Resources/Models/skydoom.cmo"))));
	// ��
	gameObjects.emplace_back(std::move(std::unique_ptr<ModelObject>(new ModelObject(L"Resources/Models/floor.cmo"))));

	// ��s�@
	auto plane = std::unique_ptr<ModelObjectControl>(new ModelObjectControl(L"Resources/Models/plane.cmo"));
	plane->transform.LocalPosition += Vector3::Up * 1;
	gameObjects.emplace_back(std::move(plane));
	Transform* t = &gameObjects.back()->transform;

	// �e
	auto shadow = std::unique_ptr<ModelObjectControl>(new ModelObjectControl(L"Resources/Models/shadow.cmo"));
	shadow->transform.LocalPosition += Vector3::Up * .01f;
	shadow->transform.LocalScale *= Vector3::One * 3;
	gameObjects.emplace_back(std::move(shadow));

	// �r�b�g
	auto bit = std::unique_ptr<BitObject>(new BitObject([](GameContext& context) { return GeometricPrimitive::CreateCone(context.GetDR().GetD3DDeviceContext()); }, Color(Colors::Blue), &plane->transform));
	bit->transform.Parent = t;
	bit->transform.LocalScale = Vector3::One * .2f;
	gameObjects.emplace_back(std::move(bit));

	// ������
	GameObjectContainer::Initialize(context);
}
