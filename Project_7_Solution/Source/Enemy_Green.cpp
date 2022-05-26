#include "Enemy_Green.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Green::Enemy_Green(int x, int y) : Enemy(x, y)
{
	UPup.PushBack({ 5,72,21,22 });
	redcurrentAnim = &UPup;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ -1.0f, -0.5f }, 100);
	path.PushBack({ -1.0f, 0.5f }, 80);
	path.PushBack({ -1.0f, 1.0f }, 80);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Green::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
