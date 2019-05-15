#pragma once
#include "StepTimer.h"
#include "DeviceResources.h"

// �J�����擾
class GameCamera
{
public:
	// �r���[�s��
	DirectX::SimpleMath::Matrix view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix projection;
};

// GameContext�C���^�[�t�F�C�X
class GameContext
{
public:
	GameContext() = default;
	virtual ~GameContext() = default;

public:
	// DeviceResource�擾
	virtual DX::DeviceResources& GetDR() = 0;
	// �^�C�}�[�擾
	virtual DX::StepTimer& GetTimer() = 0;
	// �J�����擾
	virtual GameCamera& GetCamera() = 0;
	// �R�����X�e�[�g�擾
	virtual DirectX::CommonStates& GetStates() = 0;
	// �G�t�F�N�g�t�@�N�g���[�擾
	virtual DirectX::EffectFactory& GetEffectFactory() = 0;
};
