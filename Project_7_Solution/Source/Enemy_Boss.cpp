#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y, movingbehaviour)
{
	fly.PushBack({ 5,72,21,22 });
	redcurrentAnim = &fly;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ -1.0f, -0.5f }, 100);
	path.PushBack({ -1.0f, 0.5f }, 80);
	path.PushBack({ -1.0f, 1.0f }, 80);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Boss::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
