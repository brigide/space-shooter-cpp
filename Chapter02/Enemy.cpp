#include "Enemy.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include <random>

Enemy::Enemy(Game* game)
	:Actor(game)
	, mRightSpeed(-100.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/pirate1.png"),
		game->GetTexture("Assets/pirate2.png"),
		game->GetTexture("Assets/pirate3.png"),
		game->GetTexture("Assets/pirate4.png"),
	};
	asc->SetAnimTextures(anims);

	int y = (rand() % 678) + 100;
	SetPosition(Vector2(900.0f, y));
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	SetPosition(pos);
}

void Enemy::ProcessKeyboard(const uint8_t* state)
{
}
