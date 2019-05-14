#pragma once

#include "DeviceResources.h"

// シングルトンDeviceResourcesラッパークラス
class DR
{
private:
	// DeviceResourcesポインタ
	std::unique_ptr<DX::DeviceResources> m_deviceResources;

public:
	DR();
	~DR();

public:
	// アロー呼び出し
	DX::DeviceResources* operator->() const;

private:
	// シングルトンstaticポインタ
	static DR* s_dr;

public:
	// シングルトン
	static DR& Get();
};
