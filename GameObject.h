#pragma once
#include "StepTimer.h"

// �Q�[���I�u�W�F�N�g
class GameObject
{
public:
	// ����
	GameObject() = default;
	// �X�V
	virtual void Update(DX::StepTimer const& timer) {};
	// �`��
	virtual void Render() {};
	// �j��
	virtual ~GameObject() = default;
};

