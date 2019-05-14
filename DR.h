#pragma once

#include "DeviceResources.h"

// �V���O���g��DeviceResources���b�p�[�N���X
class DR
{
private:
	// DeviceResources�|�C���^
	std::unique_ptr<DX::DeviceResources> m_deviceResources;

public:
	DR();
	~DR();

public:
	// �A���[�Ăяo��
	DX::DeviceResources* operator->() const;

private:
	// �V���O���g��static�|�C���^
	static DR* s_dr;

public:
	// �V���O���g��
	static DR& Get();
};
