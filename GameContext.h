#pragma once
#include "StepTimer.h"
#include "DeviceResources.h"
#include <SimpleMath.h>

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
// �����VC++�ŗL�d�l��__interface���g���Ă݂��B(�w�Z�Ƃ��Ăǂ��Ȃ̂��͕s��)
__interface GameContext
{
public:
	// DeviceResource�擾
	DX::DeviceResources& GetDR();
	// �^�C�}�[�擾
	DX::StepTimer& GetTimer();
	// �J�����擾
	GameCamera& GetCamera();
};

