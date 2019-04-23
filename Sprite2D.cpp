#include "pch.h"

#include <direct.h>
#include "Sprite2D.h"
#include <WICTextureLoader.h>
#include <SimpleMath.h>

using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace DirectX::SimpleMath;

Sprite2D::Sprite2D()
{
}

Sprite2D::~Sprite2D()
{
}

void Sprite2D::Create(ID3D11Device1* device, ID3D11DeviceContext1* context, std::wstring str)
{
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
	ComPtr<ID3D11Resource> resource;
	CreateWICTextureFromFile(device, str.c_str(), resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf());

	//D3D11_SHADER_RESOURCE_VIEW_DESC *res;
	//m_texture->GetDesc(res);
	//res.D
}

void Sprite2D::Reset()
{
	m_texture.Reset();
	m_spriteBatch.reset();
}

void Sprite2D::Draw()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_pos);
	m_spriteBatch->End();
}

void Sprite2D::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	m_pos += Vector2::One * elapsedTime * 100;
}
