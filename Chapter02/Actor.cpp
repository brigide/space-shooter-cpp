// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(EActive)//estado do ator, ativo ou desativado
	, mPosition(Vector2::Zero)//coordenadas para posicionar o ator
	, mScale(1.0f)//escala
	, mRotation(0.0f)//parametros para rota��o do ator, se necess�rio
	, mGame(game)//aponta para a classe Game
{
	mGame->AddActor(this);//adiciona esse ator ao jogo
}

Actor::~Actor()//destrutor do ator
{
	mGame->RemoveActor(this);
	//componentes tem qeu ser removidos
	//notem que n�o vamos destruir os componentes, mas apenas remov�-los
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)//atualiza o ator
{
	if (mState == EActive)//verifica se ele est� ativo
	{
		UpdateComponents(deltaTime);//atualiza seus componentes em fun��o do delta time transcorrido
		UpdateActor(deltaTime);//atualiza ent�o o ator com base na atualiza��o de seus componentes
	}
}

void Actor::UpdateComponents(float deltaTime)//atualiza os componentes do ator
{
	for (auto comp : mComponents)//itera sobre cada um dos componentes
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)//declara��o da fun��o de atualiza��o do ator
{
}

void Actor::AddComponent(Component* component)//fun��o para adicionar um componentes
{
	// descobre em que ponto do vetor de componentes o novo componente deve ser inserido
	// 
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// insere o elemento na ordem desejada
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)//remove componentes
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
