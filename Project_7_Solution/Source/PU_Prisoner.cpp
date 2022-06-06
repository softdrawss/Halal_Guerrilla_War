#include "PU_Prisoner.h"
#include "Application.h"
#include "SDL/include/SDL_render.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "PowerUp.h"

PU_Prisoner::PU_Prisoner(int x, int y) : PowerUp(x, y)
{
	
	help.PushBack({ 5, 2, 30, 57 });
	help.PushBack({ 35, 2, 30, 57 });
	help.PushBack({ 73, 2, 30, 57 });
	help.PushBack({ 103, 2, 30, 57 });
	
	saved.PushBack({ 2, 74, 30, 57 });

	death.PushBack({});
	currentAnim = &help;
	//put collider
	collider = App->collisions->AddCollider({ 0, 0, 18, 54 }, Collider::Type::PRISONER, (Module*)App->powerUps);

}


void PU_Prisoner::Update()
{
	currentAnim = &help;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PowerUp::Update();
}
