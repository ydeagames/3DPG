#pragma once

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"
#include "StepTimer.h"

class Sprite2D
{
public:
	Sprite2D();
	~Sprite2D();

public:
	void Create(ID3D11Device1 * device, ID3D11DeviceContext1 * context, std::wstring str);
	void Reset();
	void Draw();
	void Update(DX::StepTimer const& timer);

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_pos;
};

