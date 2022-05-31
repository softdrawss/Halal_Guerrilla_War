#include "Enemy_Red.h"
#include "SDL/include/SDL_render.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Application.h"
#include "Enemy.h"
Enemy_Red::Enemy_Red(int x, int y, int movingbehaviour) : Enemy(x, y, movingbehaviour)
{
	//pushbacks for the animations
	Eup.PushBack({1,1,22,48});
	Eupright.PushBack({ 30,6,30,43 });
	Eright.PushBack({ 71,8,33,41 });
	Edownright.PushBack({ 105,8,28,43 });
	Edown.PushBack({ 138,8,25,45 });
	Edownleft.PushBack({ 164,8,32,42 });
	Eleft.PushBack({ 196,8,35,41 });
	Eupleft.PushBack({ 233,5,32,51 });

	//put collider
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);

}


void Enemy_Red::Update()
{
	if (up == true) {
		redcurrentAnim = &Eup;
	}
	else if (down == true) {
		redcurrentAnim = &Edown;
	}
	else if (right == true) {
		redcurrentAnim = &Eright;
	}
	else if (left == true) {
		redcurrentAnim = &Eleft;
	}
	else if (upright == true) {
		redcurrentAnim = &Eupright;
	}
	else if (downright == true) {
		redcurrentAnim = &Edownright;
	}
	else if (downleft == true) {
		redcurrentAnim = &Edownleft;
	}
	else if (upleft == true) {
		redcurrentAnim = &Eupleft;
	}

	Attack();
	App->particles->Update();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
