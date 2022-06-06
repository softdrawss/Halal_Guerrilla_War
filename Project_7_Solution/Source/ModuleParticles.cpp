

#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
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
		textureExplosion = App->textures->Load("Assets/Guerrilla War Explosions Spritesheet.png");
		missiletexture = App->textures->Load("Assets/Guerrilla War Boss Spritesheet.png");

		//horitzontal right shot
		normal_hr_shot.anim.PushBack({ 67, 183, 9, 3 });
		normal_hr_shot.anim.PushBack({ 84, 183, 9, 3 });
		normal_hr_shot.speed.x = 8;
		normal_hr_shot.anim.speed = 0.2f;
		normal_hr_shot.lifetime = 18;
		normal_hr_shot.hasExplosion = false;

		//horitzontal left shot
		normal_hl_shot.anim.PushBack({ 196, 182,9,3 });
		normal_hl_shot.anim.PushBack({ 196, 182,9,3 });
		normal_hl_shot.speed.x = -8;
		normal_hl_shot.anim.speed = 0.2f;
		normal_hl_shot.lifetime = 18;
		normal_hl_shot.hasExplosion = false;

		// up shot
		normal_up_shot.anim.PushBack({ 7, 180,3,9 });
		normal_up_shot.anim.PushBack({ 23, 180,3,9 });
		normal_up_shot.speed.y = -8;
		normal_up_shot.anim.speed = 0.2f;
		normal_up_shot.lifetime = 18;
		normal_up_shot.hasExplosion = false;

		// down shot
		normal_down_shot.anim.PushBack({ 134,179,3,9 });
		normal_down_shot.anim.PushBack({ 150,180,3,9 });
		normal_down_shot.speed.y = 8;
		normal_down_shot.anim.speed = 0.2f;
		normal_down_shot.lifetime = 18;
		normal_down_shot.hasExplosion = false;

		//horitzontal right up shot
		normal_ur_shot.anim.PushBack({ 36,181,7,7 });
		normal_ur_shot.anim.PushBack({ 52,181,7,7 });
		normal_ur_shot.speed.y = -8;
		normal_ur_shot.speed.x = 8;
		normal_ur_shot.anim.speed = 0.2f;
		normal_ur_shot.lifetime = 18;
		normal_ur_shot.hasExplosion = false;

		//horitzontal left up shot
		normal_ul_shot.anim.PushBack({ 229,181,7,7 });
		normal_ul_shot.anim.PushBack({ 245,181,7,7 });
		normal_ul_shot.speed.y = -8;
		normal_ul_shot.speed.x = -8;
		normal_ul_shot.anim.speed = 0.2f;
		normal_ul_shot.lifetime = 18;
		normal_ul_shot.hasExplosion = false;

		//hortizontal right down shot
		normal_dr_shot.anim.PushBack({ 99,180,7,7 });
		normal_dr_shot.anim.PushBack({ 115,180,7,7 });
		normal_dr_shot.speed.y = 8;
		normal_dr_shot.speed.x = 8;
		normal_dr_shot.anim.speed = 0.2f;
		normal_dr_shot.lifetime = 18;
		normal_dr_shot.hasExplosion = false;

		//horitzontal left down shot;
		normal_dl_shot.anim.PushBack({ 165,180,7,7 });
		normal_dl_shot.anim.PushBack({ 165,180,7,7 });
		normal_dl_shot.speed.y = 8;
		normal_dl_shot.speed.x = -8;
		normal_dl_shot.anim.speed = 0.2f;
		normal_dl_shot.lifetime = 18;
		normal_dl_shot.hasExplosion = false;

		//grenade up
		grenade.anim.PushBack({ 1,160,15,15 });
		grenade.anim.PushBack({ 18,161,13,13 });
		grenade.anim.PushBack({ 35,162,11,11 });
		grenade.anim.PushBack({ 50,162,11,12 });
		grenade.anim.PushBack({ 66,164,11,10 });
		grenade.anim.PushBack({ 82,162,13,13 });
		grenade.anim.PushBack({ 96,161,15,15 });
		grenade.anim.PushBack({ 114,161,14,14 });
		grenade.anim.PushBack({ 131,161,12,13 });
		grenade.anim.PushBack({ 146,162,12,12 });
		grenade.anim.PushBack({ 161,162,13,12 });
		grenade.anim.PushBack({ 177,161,14,14 });
		grenade.lifetime = 60;
		grenade.anim.speed = 0.2f;
		grenade.hasExplosion = true;
		grenade.explosioncounter = 100;

		// Explosion particle
		explosion.anim.PushBack({ 9, 13, 48, 49 });
		explosion.anim.PushBack({ 71, 11, 50, 50 });
		explosion.anim.PushBack({ 130, 3, 60, 60 });
		explosion.anim.PushBack({ 196, 4, 56, 59 });
		explosion.anim.PushBack({ 261, 0, 55, 63 });
		explosion.anim.PushBack({ 320, 0, 64, 62 });
		explosion.anim.loop = false;
		explosion.anim.speed = 0.15f;
		explosion.hasExplosion = false;
		explosion.lifetime =28;
		explosion.isexplosion = true;

		//sprites for the enemy bullets
		enemybullet.anim.PushBack({ 198,66,4,5 });
		enemybullet.anim.PushBack({ 214,66,4,5 });
		enemybullet.anim.loop = true;
		enemybullet.lifetime = 80;
		enemybullet.anim.speed = 0.2f;
		enemybullet.hasExplosion = false;

		//sprites for the missiles of the boss

		missileup.anim.PushBack({ 130,160,12,16 });
		missileup.anim.PushBack({ 148,160,8,16 });
		missileup.anim.loop = true;
		missileup.lifetime = 180;
		missileup.anim.speed = 0.2f;
		missileup.hasExplosion = true;
		missileup.ismissile = true;
		missileup.speed.y = -2;

		missiledown.anim.PushBack({ 20,160,12,16 });
		missiledown.anim.PushBack({ 2,160,8,16 });
		missiledown.anim.loop = true;
		missiledown.lifetime = 60;
		missiledown.anim.speed = 0.2f;
		missiledown.hasExplosion = true;
		missiledown.ismissile = true;
		missiledown.speed.y = 2;

		missileleft.anim.PushBack({ 192,162,16,12 });
		missileleft.anim.PushBack({ 208,164,16,8 });
		missileleft.anim.loop = true;
		missileleft.lifetime = 60;
		missileleft.anim.speed = 0.2f;
		missileleft.hasExplosion = true;
		missileleft.ismissile = true;
		missileleft.speed.x = -2;

		missileright.anim.PushBack({ 64,162,18,12 });
		missileright.anim.PushBack({ 83,164,14,8 });
		missileright.anim.loop = true;
		missileright.lifetime = 60;
		missileright.anim.speed = 0.2f;
		missileright.hasExplosion = true;
		missileright.ismissile = true;
		missileright.speed.x = 2;

		missileur.anim.PushBack({ 96,160,15,16 });
		missileur.anim.PushBack({ 113,160,15,15 });
		missileur.anim.loop = true;
		missileur.lifetime = 180;
		missileur.anim.speed = 0.2f;
		missileur.hasExplosion = true;
		missileur.ismissile = true;
		missileur.speed.y = -1;
		missileur.speed.x = 1;

		missileul.anim.PushBack({ 160,160,15,16 });
		missileul.anim.PushBack({ 176,160,14,15 });
		missileul.anim.loop = true;
		missileul.lifetime = 180;
		missileul.anim.speed = 0.2f;
		missileul.hasExplosion = true;
		missileul.ismissile = true;
		missileul.speed.y = -1;
		missileul.speed.x = -1;

		missiledr.anim.PushBack({ 33,160,15,16 });
		missiledr.anim.PushBack({ 50,161,14,15 });
		missiledr.anim.loop = true;
		missiledr.lifetime = 60;
		missiledr.anim.speed = 0.2f;
		missiledr.hasExplosion = true;
		missiledr.ismissile = true;
		missiledr.speed.y = 1;
		missiledr.speed.x = 1;

		missiledl.anim.PushBack({ 224,161,16,15 });
		missiledl.anim.PushBack({ 240,161,16,15 });
		missiledl.anim.loop = true;
		missiledl.lifetime = 60;
		missiledl.anim.speed = 0.2f;
		missiledl.hasExplosion = true;
		missiledl.ismissile = true;
		missiledl.speed.y = 1;
		missiledl.speed.x = -1;

		return true;
	}

	Update_Status ModuleParticles::PreUpdate()
	{
		// Remove all particles scheduled for deletion
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (particles[i] != nullptr && particles[i]->pendingToDelete)
			{
				delete particles[i];
				particles[i] = nullptr;
			}
		}

		return Update_Status::UPDATE_CONTINUE;
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
				particles[i]->pendingToDelete = true;
				particles[i]->collider->pendingToDelete = true;
				break;
			}
		}
	}

	Update_Status ModuleParticles::Update()
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			Particle* particle = particles[i];

			if (particle == nullptr) {
				continue;
			}	
			
			// Call particle Update. If it has reached its lifetime, destroy it
			if (particle->Update() == false)
			{
				if (particle->hasExplosion == true) {
					uint explode = App->audio->LoadFx("Assets/gwar-147.wav");
					App->audio->PlayFx(explode, 0);
					AddParticle(explosion, particle->position.x, particle->position.y, Collider::Type::EXPLOSION);
					App->player->isgrenade = false;
					App->player->grenadeanimcounter = 10;
				}
				particles[i]->SetToDelete();
			}
		}
		return Update_Status::UPDATE_CONTINUE;
	}

	Update_Status ModuleParticles::PostUpdate()
	{
		//Iterating all particle array and drawing any active particles
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			Particle* particle = particles[i];

			if (particle != nullptr && particle->isAlive)
			{
				if (particle->isexplosion == true) {
					App->render->Blit(textureExplosion, particle->position.x-25, particle->position.y-25, &(particle->anim.GetCurrentFrame()));
				}
				else if (particle->ismissile == true) {
					App->render->Blit(missiletexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
				}
				else {
					App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
				}

			}
		}

		return Update_Status::UPDATE_CONTINUE;
	}

	Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
	{
		Particle* newParticle = nullptr;

		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			//Finding an empty slot for a new particle
			if (particles[i] == nullptr)
			{
				newParticle = new Particle(particle);
				newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
				newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
				newParticle->position.y = y;

				//Adding the particle's collider
				if (colliderType != Collider::Type::NONE) {
					if (newParticle->isexplosion == true) {
						newParticle->collider = App->collisions->AddCollider({x-10,y-5,30,30}, colliderType);
					}
					else {
						newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);
					}
				}
					
					

				particles[i] = newParticle;
				break;
			}
		}

		return newParticle;
	}