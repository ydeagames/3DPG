#include "pch.h"
#include "GameObjectContainer.h"

void GameObjectContainer::Update(DX::StepTimer const& timer)
{
	for (auto& object : gameObjects)
		object->Update(timer);
}

void GameObjectContainer::Render()
{
	for (auto& object : gameObjects)
		object->Render();
}
