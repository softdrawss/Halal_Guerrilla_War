#include "ModulePowerUp.h"
#include "Application.h"
#include "PowerUp.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
//
//#include "Enemy.h"
//#include "Enemy_Red.h"
//#include "Enemy_Green.h"
//#include "Enemy_Green_Bomb.h"
//#include "Enemy_Boss.h"
//#include "Enemy_Truck.h"

#define SPAWN_MARGIN2 50

//need to edit
ModulePowerUp::ModulePowerUp(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerups[i] = nullptr;
}

ModulePowerUp::~ModulePowerUp()
{

}

bool ModulePowerUp::Start()
{
	texturePRISONER = App->textures->Load("Assets/EnemySpriteRec.png");
	textureWEAPON = App->textures->Load("Assets/Guerrilla War Weapon Spritesheet.png");
	

	return true;
}

Update_Status ModulePowerUp::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->pendingToDelete)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePowerUp::Update()
{
	HandlePowerUpSpawn();

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
			powerups[i]->Update();
	}

	HandlePowerUpDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePowerUp::PostUpdate()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
			powerups[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePowerUp::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return true;
}

bool ModulePowerUp::AddPowerUp(PowerUp_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (spawnQueue[i].type == PowerUp_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}


void ModulePowerUp::HandlePowerUpSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (spawnQueue[i].type != PowerUp_Type::NO_TYPE)
		{
			LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

			SpawnPowerUp(spawnQueue[i]);
			spawnQueue[i].type = PowerUp_Type::NO_TYPE; // Removing the newly spawned enemy from the queue

		}
	}
}

void ModulePowerUp::HandlePowerUpDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (powerups[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN2)
			{
				LOG("DeSpawning enemy at %d", powerups[i]->position.x * SCREEN_SIZE);

				powerups[i]->SetToDelete();
			}
		}
	}
}

void ModulePowerUp::SpawnPowerUp(const PowerUpSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] == nullptr)
		{
			switch (info.type)
			{
			case PowerUp_Type::PRISONER:
				//powerups[i] = new Enemy_Green_Bomb(info.x, info.y);
				powerups[i]->texture = texturePRISONER;
				break;
			case PowerUp_Type::WEAPON:
				//enemies[i] = new Enemy_Boss(info.x, info.y);
				powerups[i]->texture = textureWEAPON;
				break;
			}

			//enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->GetCollider() == c1)
		{
			powerups[i]->OnCollision(c2); //Notify the enemy of a collision
			if (powerups[i]->deathcounter == 100) {
				delete powerups[i];
				powerups[i] = nullptr;
			}

			break;
		}
	}
}