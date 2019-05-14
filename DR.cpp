#include "pch.h"

#include "DR.h"

// シングルトンstaticポインタ
DR* DR::s_dr = nullptr;

DR::DR()
	: m_deviceResources(nullptr)
{
	// 二度目はない
	if (s_dr)
		throw std::exception("DR is a singleton");
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	// staticポインタにセット
	s_dr = this;
}

DR::~DR()
{
	// staticポインタを削除
	s_dr = nullptr;
}

// アロー呼び出し
DX::DeviceResources* DR::operator->() const
{
	// ポインタ返却
	return m_deviceResources.get();
}

// シングルトン
DR& DR::Get()
{
	// 初期化が必要
	if (!s_dr)
		throw std::exception("DR is a singleton");
	// シングルトンポインタ返却
	return *s_dr;
}
