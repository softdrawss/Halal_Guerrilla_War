#include "PowerUp.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

PowerUp::PowerUp(int x, int y) : position(x, y)
{
	spawnPos = position;
}

PowerUp::~PowerUp()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* PowerUp::GetCollider() const
{
	return collider;
}

void PowerUp::Update()
{

	if (prisonercurrentAnim != nullptr) {
		prisonercurrentAnim->Update();
	}

	if (weaponcurrentAnim != nullptr) {
		weaponcurrentAnim->Update();
	}


	if (collider != nullptr)
		collider->SetPos(position.x, position.y);


}

void PowerUp::Draw()
{
	if (prisonercurrentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(prisonercurrentAnim->GetCurrentFrame()));
	}


	if (weaponcurrentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(weaponcurrentAnim->GetCurrentFrame()));
	}

}

void PowerUp::OnCollision(Collider* collider)
{
	//should be only when collision type = player shot
	//if ((collider->Intersects(c2->rect) == true)
	//int destroyedFx = App->audio->LoadFx("Assets/gwar-198.wav");
	//App->audio->PlayFx(destroyedFx, 0);

	SetToDelete();
	}

void PowerUp::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}