//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include <WICTextureLoader.h>
#include "DebugFont.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	sprite.Update(timer);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

	// --------------------------------------------------------------------------
	
	// ���_�C���f�b�N�X
	static uint16_t s_indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
	};
	// ���_���W�e�[�u��
	static VertexPositionNormal s_vertices[] =
	{
		{ Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(XMConvertToRadians(60 * 0))), Vector3::Backward },
		{ Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(XMConvertToRadians(60 * 1))), Vector3::Backward },
		{ Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(XMConvertToRadians(60 * 2))), Vector3::Backward },
		{ Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(XMConvertToRadians(60 * 3))), Vector3::Backward },
		{ Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(XMConvertToRadians(60 * 4))), Vector3::Backward },
		{ Vector3::Transform(Vector3::Up, Matrix::CreateRotationZ(XMConvertToRadians(60 * 5))), Vector3::Backward },
	};

	// TODO: Add your rendering code here.
	sprite.Draw();

	SimpleMath::Matrix world;
	SimpleMath::Matrix view;
	SimpleMath::Matrix proj;
	// �r���[�s����Z�o����
	SimpleMath::Vector3 eye(0.0f, 0.0f, 10.0f);
	SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	view = SimpleMath::Matrix::CreateLookAt(eye, target, up);
	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);
	// ��p��ݒ�
	float fovAngleY = XMConvertToRadians(45.0f);
	// �ˉe�s����쐬����
	proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
	);
	// ���[���h�s��ݒ�
	m_pBasicEffect->SetWorld(world);
	// �r���[�s��ݒ�
	m_pBasicEffect->SetView(view);
	// �v���W�F�N�V�����s��ݒ�
	m_pBasicEffect->SetProjection(proj);
	// �G�t�F�N�g�̐ݒ�
	m_pBasicEffect->Apply(context);
	// �[�x�X�e���V���X�e�[�g�̐ݒ�
	context->OMSetDepthStencilState(m_state->DepthDefault(), 0);
	// �u�����h�X�e�[�g�̐ݒ�
	context->OMSetBlendState(m_state->AlphaBlend(), nullptr, 0xffffffff);
	// ���X�^���C�U�X�e�[�g��ݒ�
	context->RSSetState(m_state->CullClockwise());
	// ���̓��C�A�E�g�̐ݒ�
	context->IASetInputLayout(m_pInputLayout.Get());
	// �`��J�n
	m_pPrimitiveBatch->Begin();
	// ���_��񂩂�`��
	m_pPrimitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, s_indices, 12, s_vertices, 6);
	// �`��I��
	m_pPrimitiveBatch->End();

	m_pLinePrimitiveBatch->Begin();
	VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f) + Vector3::Right * 4, Colors::White);
	VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f) + Vector3::Right * 4, Colors::White);
	m_pLinePrimitiveBatch->DrawLine(v1, v2);
	m_pLinePrimitiveBatch->End();

	DebugFont::GetInstance()->print(Vector2::Zero, L"FPS: %d", m_timer.GetFramesPerSecond());
	DebugFont::GetInstance()->draw();

	// --------------------------------------------------------------------------

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
	auto context = m_deviceResources->GetD3DDeviceContext();

	sprite.Create(device, context, L"slime.png");

	// �R�����X�e�[�g�쐬
	m_state = std::make_unique<CommonStates>(device);
	// �v���~�e�B�u�o�b�`�쐬
	m_pPrimitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(context);
	// �v���~�e�B�u�o�b�`�쐬
	m_pLinePrimitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
	// �|���S���p�G�t�F�N�g�쐬
	m_pBasicEffect = std::make_unique<BasicEffect>(device);
	// ���C�g�L��
	m_pBasicEffect->SetLightingEnabled(true);
	// �����̐F��ݒ�
	m_pBasicEffect->SetAmbientLightColor(SimpleMath::Vector3(0.2f, 0.2f, 0.2f));
	// �g�U���ˌ��̑f�ސF��ݒ�
	m_pBasicEffect->SetDiffuseColor(SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	// ���C�g�O�Ԃ�L��
	m_pBasicEffect->SetLightEnabled(0, true);
	// ���C�g�O�Ԃ̐F�ݒ�
	m_pBasicEffect->SetLightDiffuseColor(0, SimpleMath::Vector3(0.2f, 0.8f, 0.2f));
	// ���C�g�O�Ԃ̌�����ݒ�
	m_pBasicEffect->SetLightDirection(0, SimpleMath::Vector3(-1.0f, -0.5f, -2.0f));
	void const * shaderByteCode;
	size_t byteCodeLength;
	// �V�F�[�_�[�擾
	m_pBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// ���̓��C�A�E�g�̍쐬�i���_�f�[�^�̒�`����j
	device->CreateInputLayout(VertexPositionNormal::InputElements,
		VertexPositionNormal::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_pInputLayout.GetAddressOf());

	DebugFont::GetInstance()->create(device, context);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

	sprite.Reset();

	m_state.reset();
	m_pInputLayout.Reset();
	m_pBasicEffect.reset();
	m_pPrimitiveBatch.reset();

	DebugFont::GetInstance()->reset();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
