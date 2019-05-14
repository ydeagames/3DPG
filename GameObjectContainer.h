#pragma once
#include "StepTimer.h"
#include "GameObject.h"

// �Q�[���I�u�W�F�N�g�R���e�i
class GameObjectContainer : public GameObject
{
public:
	// �q�Q�[���I�u�W�F�N�g
	std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
	// �X�V
	void Update(DX::StepTimer const& timer);
	// �`��
	void Render();
};