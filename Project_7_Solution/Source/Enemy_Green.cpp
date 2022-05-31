#include "Enemy_Green.h"
#include "SDL/include/SDL_render.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Application.h"
#include "Enemy.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

Enemy_Green::Enemy_Green(int x, int y, int movingbehaviour) : Enemy(x, y, movingbehaviour)
{
	this->movingbehaviour = movingbehaviour;

	//pushbacks for the looking animations
	Eup.PushBack({ 345,451,32,64 });
	Eupright.PushBack({ 388,451,32,64 });
	Eright.PushBack({ 424,451,32,64 });
	Edownright.PushBack({ 468,451,32,64 });
	Edown.PushBack({ 504,459,32,64 });
	Edownleft.PushBack({ 550,459,32,64 });
	Eleft.PushBack({ 604,459,32,64 });
	Eupleft.PushBack({ 668,459,32,64 });

	uEwalkdown.PushBack({ 238,60,32,32 });
	uEwalkdown.PushBack({ 272,60,32,32 });
	uEwalkdown.PushBack({ 305,60,32,32 });
	bEwalkdown.pingpong = true;
	uEwalkdown.speed = 0.15f;

	bEwalkdown.PushBack({ 335,190,32,32 });
	bEwalkdown.PushBack({ 370,190,32,32 });
	bEwalkdown.PushBack({ 398,190,32,32 });
	bEwalkdown.PushBack({ 431,190,32,32 });
	bEwalkdown.PushBack({ 463,190,32,32 });
	bEwalkdown.PushBack({ 431,190,32,32 });
	bEwalkdown.PushBack({ 398,190,32,32 });
	bEwalkdown.PushBack({ 370,190,32,32 });
	bEwalkdown.pingpong = true;
	bEwalkdown.speed = 0.15f;

	uEwalkup.PushBack({ 239,189,32,32 });
	uEwalkup.PushBack({ 271,190,32,32 });
	uEwalkup.PushBack({ 303,188,32,32 });
	uEwalkup.pingpong = true;
	uEwalkup.speed = 0.15f;

	bEwalkup.PushBack({ 334,62,32,32 });
	bEwalkup.PushBack({ 366,62,32,32 });
	bEwalkup.PushBack({ 400,62,32,32 });
	bEwalkup.PushBack({ 430,62,32,32 });
	bEwalkup.PushBack({ 462,62,32,32 });
	bEwalkup.pingpong = true;
	bEwalkup.speed = 0.15f;


	pathup.PushBack({ 0.0f, -1.5f }, 100, &bEwalkup);
	pathdown.PushBack({ 0.0f, 1.5f }, 100, &bEwalkdown);

	//death anim
	deathanim.PushBack({ 240,384,32,64 });
	deathanim.PushBack({ 272,384,32,64 });
	deathanim.PushBack({ 306,384,32,64 });
	deathanim.PushBack({ 336,384,32,64 });
	deathanim.PushBack({ 367,384,32,64 });
	deathanim.PushBack({ 396,384,32,64 });
	deathanim.PushBack({ 427,384,32,64 });
	deathanim.PushBack({ 461,384,32,64 });
	deathanim.PushBack({ 495,384,32,64 });
	deathanim.PushBack({ 528,384,32,64 });
	deathanim.PushBack({ 560,384,32,64 });
	deathanim.PushBack({ 592,384,32,64 });
	deathanim.PushBack({ 624,384,32,64 });
	deathanim.speed = 0.2f;
	deathanim.loop = false;


	ismoving = false;
	
	
	// TODO 3: Have the Brown Cookies describe a path in the screen
	delay1 = bulletscounter = 0;
	jajabool = false;
	reachendpath = false;
	dead = false;
	deathcounter = 0;


	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Green::Update()
{

	if (dead == true) {
		if (deathcounter >= 70) {
			SetToDelete();
		}
		currentdeathanim = &deathanim;
		++deathcounter;
	}
	else if (movingbehaviour == 0) {
		dontmove();
	}
	else if (movingbehaviour == 1) {
		godownshootgoup();
	}

	App->particles->Update();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Green::godownshootgoup() {
	if (reachendpath == false) {
		if (position.y <= spawnPos.y + 200) {
			ismoving = true;
			pathdown.Update();
			position = spawnPos + pathdown.GetRelativePosition();
			greenlegscurrentAnim = pathdown.GetCurrentAnimation();
			greentorsocurrentAnim = &uEwalkdown;
			if (position.y >= spawnPos.y + 201) {
				reachendpath = true;
			}

		}
	}
	else {
		if (waitforshoot == 100) {
			jajabool = true;
		}

		if (jajabool == true) {
			ismoving = true;
			pathup.Update();
			position = spawnPos + pathdown.GetRelativePosition() + pathup.GetRelativePosition();
			greenlegscurrentAnim = pathup.GetCurrentAnimation();
			greentorsocurrentAnim = &uEwalkup;
		}
		else {
			ismoving = false;
			greencurrentAnim = &Edown;
			Attackdown();
			++waitforshoot;
		}
	}
}

void Enemy_Green::dontmove() {
	if (up == true) {
		greencurrentAnim = &Eup;
	}
	else if (down == true) {
		greencurrentAnim = &Edown;
	}
	else if (right == true) {
		greencurrentAnim = &Eright;
	}
	else if (left == true) {
		greencurrentAnim = &Eleft;
	}
	else if (upright == true) {
		greencurrentAnim = &Eupright;
	}
	else if (downright == true) {
		greencurrentAnim = &Edownright;
	}
	else if (downleft == true) {
		greencurrentAnim  = &Edownleft;
	}
	else if (upleft == true) {
		greencurrentAnim = &Eupleft;
	}

	Attack();
	App->particles->Update();
	
}

void Enemy_Green::OnCollision(Collider* collider){
	dead = true;
	int destroyedFx = App->audio->LoadFx("Assets/gwar-198.wav");
	App->audio->PlayFx(destroyedFx, 0);
	App->player->score += 100;
}