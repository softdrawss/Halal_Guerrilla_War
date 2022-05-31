
#include "Enemy.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;

	degrees = angle = 0.0f;

	up = false;
	down = false;
	right = false;
	left = false;
	upright = false;
	upleft = false;
	downright = false;
	downleft = false;

}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{


	facingtoplayer();
	direction();


	if (redcurrentAnim != nullptr)
		redcurrentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


}

void Enemy::facingtoplayer() {
	rx = App->player->position.x - this->position.x;
	ry = -(App->player->position.y - this->position.y);
	angle = atan2(ry, rx);
	degrees = angle / (M_PI / 180.0);
	if (degrees < 0) {
		degrees += 360.0f;
	}
}

void Enemy::direction() {
	if (degrees > -22.5 && degrees <= 22.5) {
		up = false;
		down = false;
		right = true;
		left = false;
		upright = false;
		upleft = false;
		downright = false;
		downleft = false;
	}
	 else if (degrees > 22.5 && degrees <= 67.5) {
		up = false;
		down = false;
		right = false;
		left = false;
		upright = true;
		upleft = false;
		downright = false;
		downleft = false;
	}
	else if (degrees > 67.5 && degrees <= 112.5) {
		up = true;
		down = false;
		right = false;
		left = false;
		upright = false;
		upleft = false;
		downright = false;
		downleft = false;
	}
	else if (degrees > 112.5 && degrees <= 157.5) {
		up = false;
		down = false;
		right = false;
		left = false;
		upright = false;
		upleft = true;
		downright = false;
		downleft = false;
	}
	else if (degrees > 157.5 && degrees <= 202.5 ) {
		up = false;
		down = false;
		right = false;
		left = true;
		upright = false;
		upleft = false;
		downright = false;
		downleft = false;
	}
	else if (degrees > 202.5 && degrees <= 247.5) {
		up = false;
		down = false;
		right = false;
		left = false;
		upright = false;
		upleft = false;
		downright = false;
		downleft = true;
	}
	else if (degrees > 247.5 && degrees <= 292.5) {
		up = false;
		down = true;
		right = false;
		left = false;
		upright = false;
		upleft = false;
		downright = false;
		downleft = false;
	}
	else if (degrees > 292.5 && degrees <= 337.5) {
		up = false;
		down = false;
		left = false;
		right = false;
		upleft = false;
		upright = false;
		downleft = false;
		downright = true;
	}
}
void Enemy::Attack() {

	


}

void Enemy::Flee() {

}


void Enemy::Draw()
{
	if (redcurrentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(redcurrentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	int destroyedFx = App->audio->LoadFx("Assets/gwar-198.wav");
	App->audio->PlayFx(destroyedFx, 0);
	
	SetToDelete();
	App->player->score+=100;
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

void Enemy::Walkdown() 
{
	position.y -= speed;
}

void Enemy::Walkdiagonalleftdown() {
	position.y -= speed;
	position.x -= speed;
}

void Enemy::Walkdiagonalrightdown() {
	position.y -= speed;
	position.x += speed;
}