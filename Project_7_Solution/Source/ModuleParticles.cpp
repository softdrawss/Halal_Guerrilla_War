

#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

	ModuleParticles::ModuleParticles()
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
			particles[i] = nullptr;
	}

	ModuleParticles::~ModuleParticles()
	{

	}

	bool ModuleParticles::Start()
	{
		LOG("Loading particles");
		texture = App->textures->Load("Assets/Guerrilla War Bullets Spritesheet.png");
		textureEnemy = App->textures->Load("Assets/Guerrilla War Deaths.png");

		// Explosion particle
		explosion.anim.PushBack({ 274, 296, 33, 30 });
		explosion.anim.PushBack({ 313, 296, 33, 30 });
		explosion.anim.PushBack({ 346, 296, 33, 30 });
		explosion.anim.PushBack({ 382, 296, 33, 30 });
		explosion.anim.PushBack({ 419, 296, 33, 30 });
		explosion.anim.PushBack({ 457, 296, 33, 30 });
		explosion.anim.loop = false;
		explosion.anim.speed = 0.3f;


		//horitzontal right shot
		normal_hr_shot.anim.PushBack({ 67, 183, 9, 3 });
		normal_hr_shot.anim.PushBack({ 84, 183, 9, 3 });
		normal_hr_shot.speed.x = 8;
		normal_hr_shot.lifetime = 180;
		normal_hr_shot.anim.speed = 0.2f;
		normal_hr_shot.lifetime = 18;

		//horitzontal left shot
		normal_hl_shot.anim.PushBack({ 196, 182,9,3 });
		normal_hl_shot.anim.PushBack({ 196, 182,9,3 });
		normal_hl_shot.speed.x = -8;
		normal_hl_shot.lifetime = 180;
		normal_hl_shot.anim.speed = 0.2f;
		normal_hl_shot.lifetime = 18;

		// up shot
		normal_up_shot.anim.PushBack({ 7, 180,3,9 });
		normal_up_shot.anim.PushBack({ 23, 180,3,9 });
		normal_up_shot.speed.y = -8;
		normal_up_shot.lifetime = 180;
		normal_up_shot.anim.speed = 0.2f;
		normal_up_shot.lifetime = 18;

		// down shot
		normal_down_shot.anim.PushBack({ 134,179,3,9 });
		normal_down_shot.anim.PushBack({ 150,180,3,9 });
		normal_down_shot.speed.y = 8;
		normal_down_shot.lifetime = 180;
		normal_down_shot.anim.speed = 0.2f;
		normal_down_shot.lifetime = 18;

		//horitzontal right up shot
		normal_ur_shot.anim.PushBack({ 36,181,7,7 });
		normal_ur_shot.anim.PushBack({ 52,181,7,7 });
		normal_ur_shot.speed.y = -8;
		normal_ur_shot.speed.x = 8;
		normal_ur_shot.lifetime = 180;
		normal_ur_shot.anim.speed = 0.2f;
		normal_ur_shot.lifetime = 18;

		//horitzontal left up shot
		normal_ul_shot.anim.PushBack({ 229,181,7,7 });
		normal_ul_shot.anim.PushBack({ 245,181,7,7 });
		normal_ul_shot.speed.y = -8;
		normal_ul_shot.speed.x = -8;
		normal_ul_shot.lifetime = 180;
		normal_ul_shot.anim.speed = 0.2f;
		normal_ul_shot.lifetime = 18;

		//hortizontal right down shot
		normal_dr_shot.anim.PushBack({ 99,180,7,7 });
		normal_dr_shot.anim.PushBack({ 115,180,7,7 });
		normal_dr_shot.speed.y = 8;
		normal_dr_shot.speed.x = 8;
		normal_dr_shot.lifetime = 180;
		normal_dr_shot.anim.speed = 0.2f;
		normal_dr_shot.lifetime = 18;

		//horitzontal left down shot;
		normal_dl_shot.anim.PushBack({ 165,180,7,7 });
		normal_dl_shot.anim.PushBack({ 165,180,7,7 });
		normal_dl_shot.speed.y = 8;
		normal_dl_shot.speed.x = -8;
		normal_dl_shot.lifetime = 180;
		normal_dl_shot.anim.speed = 0.2f;
		normal_dl_shot.lifetime = 18;

		//grenade up
		grenade_up.anim.PushBack({ 1,160,15,15 });
		grenade_up.anim.PushBack({ 18,161,13,13 });
		grenade_up.anim.PushBack({ 35,162,11,11 });
		grenade_up.anim.PushBack({ 50,162,11,12 });
		grenade_up.anim.PushBack({ 66,164,11,10 });
		grenade_up.anim.PushBack({ 82,162,13,13 });
		grenade_up.anim.PushBack({ 96,161,15,15 });
		grenade_up.anim.PushBack({ 114,161,14,14 });
		grenade_up.anim.PushBack({ 131,161,12,13 });
		grenade_up.anim.PushBack({ 146,162,12,12 });
		grenade_up.anim.PushBack({ 161,162,13,12 });
		grenade_up.anim.PushBack({ 177,161,14,14 });
		grenade_up.speed.y = -2;
		grenade_up.lifetime = 60;
		grenade_up.anim.speed = 0.2f;


		return true;
	}

	bool ModuleParticles::CleanUp()
	{
		LOG("Unloading particles");

		// Delete all remaining active particles on application exit 
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (particles[i] != nullptr)
			{
				delete particles[i];
				particles[i] = nullptr;
			}
		}

		return true;
	}

	void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			// Always destroy particles that collide
			if (particles[i] != nullptr && particles[i]->collider == c1)
			{
				delete particles[i];
				particles[i] = nullptr;
				break;
			}
		}
	}

	update_status ModuleParticles::Update()
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			Particle* particle = particles[i];

			if (particle == nullptr)	continue;

			// Call particle Update. If it has reached its lifetime, destroy it
			if (particle->Update() == false)
			{
				delete particle;
				particles[i] = nullptr;
			}
		}

		return update_status::UPDATE_CONTINUE;
	}

	update_status ModuleParticles::PostUpdate()
	{
		//Iterating all particle array and drawing any active particles
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			Particle* particle = particles[i];

			if (particle != nullptr && particle->isAlive)
			{
				App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			}
		}

		return update_status::UPDATE_CONTINUE;
	}

	void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			//Finding an empty slot for a new particle
			if (particles[i] == nullptr)
			{
				Particle* p = new Particle(particle);

				p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
				p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
				p->position.y = y;

				//Adding the particle's collider
				if (colliderType != Collider::Type::NONE)
					p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

				particles[i] = p;
				break;
			}
		}
	}