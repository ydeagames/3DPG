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

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);

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

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_state;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_pPrimitiveBatch;
	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// ライン用プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_pLinePrimitiveBatch;
};