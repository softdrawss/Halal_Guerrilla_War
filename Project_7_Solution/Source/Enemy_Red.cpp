#include "Enemy_Red.h"
#include "SDL/include/SDL_render.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Application.h"
#include "Enemy.h"
Enemy_Red::Enemy_Red(int x, int y) : Enemy(x, y)
{
	down.PushBack({ 11,8,24,54 });
	currentAnim = &down;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	//path.PushBack({ -1.0f, -0.5f }, 100);
	//path.PushBack({ -1.0f, 0.5f }, 80);
	//path.PushBack({ -1.0f, 1.0f }, 80);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
	//attack = App->collisions->AddCollider({ x, y, 50, 50 }, Collider::Type::ATTACK, (Module*)App->enemies);
	attack = App->collisions->AddSpecialCollider(x,y,50, Collider::Type::ATTACK, (Module*)App->enemies);
	//SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
	//SDL_SetRenderDrawColor(Renderer, 106, 90, 205, 1);

	//SDL_RenderDrawLine(Renderer, x, y, App->player->position.x, App->player->position.y);
}

void Enemy_Red::Attack(Collider* c1, Collider* c2) {
	while (alive = true) {
		App->particles->AddParticle(App->particles->normal_down_shot, position.x + 20, position.y + 20, Collider::Type::ENEMY_SHOT);
		if (c1 == colliderEnemy && alive == true)
	{
		//App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		//App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		//App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		//App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		//App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		//App->audio->PlayFx(explosionFx);

		//destroyed = true;

		switch (c2->type) {
		
		
		case(Collider::Type::PLAYER_SHOT):
			if (collider->Intersects(c2->rect)) {
				//currentAnimation = &death;
				//currentAnimation->Update();
				alive = false;
			}
			break;
		}
	}
	}

	
}

void Enemy_Red::Update()
{
	path.Update();
	Enemy::Attack();
	position = spawnPos; //+path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
