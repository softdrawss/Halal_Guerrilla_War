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
	Eup.PushBack({1,1,22,48});
	Eupright.PushBack({ 30,6,30,43 });
	Eright.PushBack({ 71,8,33,41 });
	Edownright.PushBack({ 105,8,28,43 });
	Edown.PushBack({ 138,8,25,45 });
	Edownleft.PushBack({ 164,8,32,42 });
	Eleft.PushBack({ 196,8,35,41 });
	Eupleft.PushBack({ 233,5,32,51 });

	// TODO 3: Have the Brown Cookies describe a path in the screen
	//path.PushBack({ -1.0f, -0.5f }, 100);
	//path.PushBack({ -1.0f, 0.5f }, 80);
	//path.PushBack({ -1.0f, 1.0f }, 80);

	//put collider
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);

	delay1 = bulletscounter = 0;

}

void Enemy_Red::Attack() {
	//while (alive == true) {
	//	if (c1 == colliderEnemy && alive == true)
	//{
	//	//App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
	//	//App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
	//	//App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
	//	//App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
	//	//App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

	//	//App->audio->PlayFx(explosionFx);

	//	//destroyed = true;

	//	switch (c2->type) {
	//	
	//	
	//	case(Collider::Type::PLAYER_SHOT):
	//		if (collider->Intersects(c2->rect)) {
	//			//currentAnimation = &death;
	//			//currentAnimation->Update();
	//			alive = false;
	//		}
	//		break;
	//	}
	//}
	//}

	if (delay1 >= 10) {
		if (bulletscounter == 3) {
			bulletscounter = 0;
			delay1 = -60;
		}
		else {

			if (up == true) {
				App->particles->enemybullet.speed.y = -1;
				App->particles->enemybullet.speed.x = 0;
				App->particles->AddParticle(App->particles->enemybullet, position.x, position.y, Collider::Type::ENEMY_SHOT);
			}
			else if (down == true) {
				App->particles->enemybullet.speed.y = +1;
				App->particles->enemybullet.speed.x = 0;
				App->particles->AddParticle(App->particles->enemybullet, position.x, position.y, Collider::Type::ENEMY_SHOT);
			}
			else if (right == true) {
				App->particles->enemybullet.speed.y = 0;
				App->particles->enemybullet.speed.x = +1;
				App->particles->AddParticle(App->particles->enemybullet, position.x, position.y, Collider::Type::ENEMY_SHOT);
			}
			else if (left == true) {
				App->particles->enemybullet.speed.y = 0;
				App->particles->enemybullet.speed.x = -1;
				App->particles->AddParticle(App->particles->enemybullet, position.x, position.y, Collider::Type::ENEMY_SHOT);
			}
			else if (upright == true) {
				App->particles->enemybullet.speed.y = -1;
				App->particles->enemybullet.speed.x = +1;
				App->particles->AddParticle(App->particles->enemybullet, position.x, position.y, Collider::Type::ENEMY_SHOT);
			}
			else if (downright == true) {
				App->particles->enemybullet.speed.y = +1;
				App->particles->enemybullet.speed.x = +1;
			}
			else if (downleft == true) {
				App->particles->enemybullet.speed.y = +1;
				App->particles->enemybullet.speed.x = -1;
			}
			else if (upleft == true) {
				App->particles->enemybullet.speed.y = -1;
				App->particles->enemybullet.speed.x = -1;
			}
			delay1 = 0;
			++bulletscounter;
		}
		
	}
	++delay1;
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
	//path.Update();
	//Enemy::Attack();
	//position = spawnPos; //+path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
