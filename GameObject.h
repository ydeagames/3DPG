#pragma once
#include "GameContext.h"

// �Q�[���I�u�W�F�N�g
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

public:
	// ����
	virtual void Initialize(GameContext& context) {};
	// �X�V
	virtual void Update(GameContext& context) {};
	// �`��
	virtual void Render(GameContext& context) {};
	// �j��
	virtual void Finalize(GameContext& context) {};
};

