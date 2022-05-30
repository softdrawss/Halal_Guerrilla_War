#include "Enemy_Truck.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Truck::Enemy_Truck(int x, int y) : Enemy(x, y)
{
	appear.PushBack({ 2,3,100,200 });
	
	redcurrentAnim = &appear;


	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_Truck::Update()
{

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
