#include "Shot.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Shot::Shot(Game* game)
	:Actor(game)
	, mRightSpeed(1000.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/tiro2.png"),
	};
	asc->SetAnimTextures(anims);

	//int y = (rand() % 678) + 100;
	//SetPosition(Vector2(900.0f, y));
}

void Shot::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	SetPosition(pos);
}

void Shot::ProcessKeyboard(const uint8_t* state)
{
}
