#include "PU_Prisoner.h"
#include "Application.h"
#include "SDL/include/SDL_render.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "PowerUp.h"

PU_Prisoner::PU_Prisoner(int x, int y) : PowerUp(x, y)
{
	
	help.PushBack({ 5, 2, 30, 57 });
	help.PushBack({ 34, 2, 30, 57 });
	help.PushBack({ 65, 2, 30, 57 });
	help.PushBack({ 96, 2, 30, 57 });

	help.speed = 0.05f;

	saved.PushBack({ 3, 74, 30, 57 });
	saved.PushBack({ 34, 74, 30, 57 });
	saved.PushBack({ 65, 74, 30, 57 });
	saved.loop = false;
	saved.speed = 0.05f;

	death.PushBack({ 5, 131, 30, 57 });
	death.PushBack({ 34, 136, 30, 57 });
	death.PushBack({ 65, 136, 30, 57 });
	death.PushBack({ 96, 136, 30, 57 });
	death.loop = false;
	death.speed = 0.05f;

	prisonercurrentAnim = &help;
	//put collider
	collider = App->collisions->AddCollider({ 0, 0, 30, 30 }, Collider::Type::PRISONER, (Module*)App->powerUps);

}


void PU_Prisoner::Update()
{
	

	if (dead == true) {
		if (deathcounter >= 70) {
			SetToDelete();
		}
		++deathcounter;
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PowerUp::Update();
}

void PU_Prisoner::OnCollision(Collider* c1, Collider* c2) {
	if (c1 == collider && dead == false)
	{
		switch (c2->type) {
		case (Collider::Type::PLAYER):
			currentDeathAnim = &saved;
			App->player->score += 1000;
			happy = App->audio->LoadFx("Assets/gwar-181.wav");
			App->audio->PlayFx(happy, 0);
			dead = true;
		case (Collider::Type::ENEMY_SHOT):
			currentAnim = &death;
			App->player->score -= 500;
			sad = App->audio->LoadFx("Assets/gwar-199.wav");
			dead = true;
		}
		/*dead = true;
		int destroyedFx = App->audio->LoadFx("Assets/gwar-198.wav");
		App->audio->PlayFx(destroyedFx, 0);*/
	}
}