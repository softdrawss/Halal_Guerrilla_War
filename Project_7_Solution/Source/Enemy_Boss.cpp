#include "Enemy_Boss.h"

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

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y, movingbehaviour)
{
	fly.PushBack({ 1,32,63,128 });
	fly.PushBack({ 65,32,63,128 });
	fly.speed = 0.2f;

	deathanim.PushBack({ 128,32,63,128 });

	bosscurrentanim = &fly;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	pathup.PushBack({ 0.0f, -1.0f }, 100,&fly);
	pathdown.PushBack({ 0.0f, 1.0f }, 100, &fly);
	pathright.PushBack({ 1.0f, 0.0f }, 100, &fly);
	pathleft.PushBack({ -1.0f, 0.0f }, 100, &fly);


	collider = App->collisions->AddCollider({ 0, 0, 63, 128 }, Collider::Type::ENEMY, (Module*)App->enemies);

	notmovingcounter = 100;
	hitpoints = 60;
}



void Enemy_Boss::Update()
{
	if (dead == true) {

		if (deathcounter >= 200) {
			SetToDelete();
		}
		if (deathcounter >= 5) {
			App->particles->AddParticle(App->particles->explosion, position.x + 16, position.y + 128, Collider::Type::NONE);
		}
		if (deathcounter >= 10) {
			App->particles->AddParticle(App->particles->explosion, position.x + 10, position.y + 2, Collider::Type::NONE);
		}
		if (deathcounter >= 20) {
			App->particles->AddParticle(App->particles->explosion, position.x + 45, position.y + 10, Collider::Type::NONE);
		}
		if (deathcounter >= 23) {
			App->particles->AddParticle(App->particles->explosion, position.x + 32, position.y + 76, Collider::Type::NONE);
		}
		if (deathcounter >= 28) {
			App->particles->AddParticle(App->particles->explosion, position.x + 60, position.y + 84, Collider::Type::NONE);
		}
		if (deathcounter >= 37) {
			App->particles->AddParticle(App->particles->explosion, position.x + 20, position.y + 98, Collider::Type::NONE);
		}
		if (deathcounter >= 59) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y + 110, Collider::Type::NONE);
		}
		if (deathcounter >= 68) {
			App->particles->AddParticle(App->particles->explosion, position.x + 31, position.y + 20, Collider::Type::NONE);
		}
		if (deathcounter >= 88) {
			App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 45, Collider::Type::NONE);
		}
		if (deathcounter >= 94) {
			App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y + 104, Collider::Type::NONE);
		}
		if (deathcounter >= 104) {
			App->particles->AddParticle(App->particles->explosion, position.x + 16, position.y + 55, Collider::Type::NONE);
		}
		if (deathcounter >= 117) {
			App->particles->AddParticle(App->particles->explosion, position.x + 53, position.y + 2, Collider::Type::NONE);
		}
		if (deathcounter >= 139) {
			App->particles->AddParticle(App->particles->explosion, position.x + 2, position.y + 10, Collider::Type::NONE);
		}
		if (deathcounter >= 148) {
			App->particles->AddParticle(App->particles->explosion, position.x + 14, position.y + 65, Collider::Type::NONE);
		}
		if (deathcounter >= 150) {
			App->particles->AddParticle(App->particles->explosion, position.x + 33, position.y + 38, Collider::Type::NONE);
		}
		if (deathcounter >= 162) {
			App->particles->AddParticle(App->particles->explosion, position.x + 56, position.y + 12, Collider::Type::NONE);
		}
		if (deathcounter >= 174) {
			App->particles->AddParticle(App->particles->explosion, position.x + 47, position.y + 24, Collider::Type::NONE);
		}
		if (deathcounter >= 180) {
			App->particles->AddParticle(App->particles->explosion, position.x + 1, position.y + 88, Collider::Type::NONE);
		}
		if (deathcounter >= 190) {
			App->particles->AddParticle(App->particles->explosion, position.x + 64, position.y + 12, Collider::Type::NONE);
		}
		currentdeathanim = &deathanim;
		++deathcounter;
	}
	else {
		movedownupshoot();
	}
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}


void Enemy_Boss::movedownupshoot() {
	if (notmovingcounter <= 0) {
		if (reachendpath == false) {
			if (position.y <= spawnPos.y + 200) {
				ismoving = true;
				pathdown.Update();
				position = spawnPos + pathdown.GetRelativePosition();
				bosscurrentanim = pathdown.GetCurrentAnimation();
				if (position.y >= spawnPos.y + 201) {
					notmovingcounter = 100;
					reachendpath = true;
				}

			}
		}
		else if (reachendpath == true) {
			ismoving = true;
			pathup.Update();
			position = spawnPos + pathdown.GetRelativePosition() + pathup.GetRelativePosition();
			bosscurrentanim = pathup.GetCurrentAnimation();
			if (position.y <= spawnPos.y) {
				pathdown.Reset();
				pathup.Reset();
				notmovingcounter = 100;
				reachendpath = false;
			}
		}
	}
	else {
		--notmovingcounter;
	}
	firemissiles();
}

void Enemy_Boss::firemissiles() {

	uint missile = App->audio->LoadFx("Assets/gwar-137.wav");

	if (delay1 >= 40) {
		if (bulletscounter == 3) {
			bulletscounter = 0;
			delay1 = -60;
		}
		else {

			if (up == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missileup, position.x + 16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileup, position.x + 32, position.y + 128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileur, position.x + 48, position.y + 128, Collider::Type::NONE);
			}
			else if (down == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missiledown, position.x+16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missiledown, position.x +32, position.y +128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missiledr, position.x+48, position.y+128, Collider::Type::NONE);
			}
			else if (right == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missileur, position.x + 16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileur, position.x + 32, position.y + 128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileright, position.x + 48, position.y + 128, Collider::Type::NONE);
			}
			else if (left == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missileleft, position.x+16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileul, position.x + 32, position.y + 128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileul, position.x + 48, position.y + 128, Collider::Type::NONE);
			}
			else if (upright == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missileur, position.x+16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileur, position.x+32, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileur, position.x+48, position.y+128, Collider::Type::NONE);
			}
			else if (downright == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missiledr, position.x+16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missiledr, position.x + 32, position.y + 128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileright, position.x + 48, position.y + 128, Collider::Type::NONE);
			}
			else if (downleft == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missiledl, position.x+16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missiledl, position.x + 32, position.y + 128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missiledown, position.x + 48, position.y + 128, Collider::Type::NONE);
			}
			else if (upleft == true) {
				App->audio->PlayFx(missile, 0);
				App->particles->AddParticle(App->particles->missileul, position.x+16, position.y+128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileul, position.x + 32, position.y + 128, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->missileul, position.x + 48, position.y + 128, Collider::Type::NONE);
			}
			delay1 = 0;
			++bulletscounter;
		}
	}
	++delay1;

}

void Enemy_Boss::OnCollision(Collider* collider) {
	if (collider->Collider::Type::EXPLOSION) {
		hitpoints -= 2;
	}
	else if (collider->Collider::Type::PLAYER) {
		--hitpoints;
	}
	else {
		--hitpoints;
	}
	
	if (hitpoints <= 0) {
		dead = true;
	}
}