#pragma once
#include "GameObject.h"

// �Q�[���I�u�W�F�N�g�R���e�i
class GameObjectContainer : public GameObject
{
public:
	// �q�Q�[���I�u�W�F�N�g
	std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
	// �j��
	void Finalize(GameContext& context);
};