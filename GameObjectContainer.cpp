#include "pch.h"
#include "GameObjectContainer.h"

void GameObjectContainer::Initialize(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Initialize(context);
}

void GameObjectContainer::Update(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Update(context);
}

void GameObjectContainer::Render(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Render(context);
}

void GameObjectContainer::Finalize(GameContext& context)
{
	for (auto& object : gameObjects)
		object->Finalize(context);
}

