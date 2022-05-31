#include "Enemy_Truck.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Truck::Enemy_Truck(int x, int y) : Enemy(x, y, movingbehaviour)
{
	appear.PushBack({ 2,3,89,55 });
	
	redcurrentAnim = &appear;


	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_Truck::Update()
{
	path.Update();
	position -= spawnPos; //+path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
