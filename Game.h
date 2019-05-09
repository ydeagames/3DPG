//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "SpriteBatch.h"
#include "SimpleMath.h"
#include "Sprite2D.h"
#include "CommonStates.h"
#include "PrimitiveBatch.h"
#include "Effects.h"
#include "VertexTypes.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "GeometricPrimitive.h"
#include <Model.h>

class DebugCamera;
class GridFloor;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
	~Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	Sprite2D sprite;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_state;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_pPrimitiveBatch;
	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// ���C���p�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_pLinePrimitiveBatch;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix				m_projection;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			m_pMouse;

	// �f�o�b�O�J����
	DebugCamera*							m_pDebugCamera;
	// �O���b�h��
	GridFloor*								m_pGridFloor;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_pState;

	// �W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive[3];

	// ���f��
	std::unique_ptr<DirectX::Model> m_pModel;

};