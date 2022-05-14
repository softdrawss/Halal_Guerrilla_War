#include "Enemy_Green_Bomb.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Green_Bomb::Enemy_Green_Bomb(int x, int y) : Enemy(x, y)
{
	still.PushBack({ 5,397,24,49 });
	attack.PushBack({ 37,397,24, 49 });
	attack.PushBack({ 69,397,24, 49 });
	attack.PushBack({ 69,397,24, 49 });
	attack.speed = 0.1f;
	currentAnim = &attack;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	//path.PushBack({ -1.0f, -0.5f }, 100);
	//path.PushBack({ -1.0f, 0.5f }, 80);
	//path.PushBack({ -1.0f, 1.0f }, 80);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
	//collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Green_Bomb::Update()
{
	//path.Update();
	position = spawnPos;
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}