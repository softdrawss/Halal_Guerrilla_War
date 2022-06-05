#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_Red.h"
#include "Enemy_Green.h"
#include "Enemy_Green_Bomb.h"
#include "Enemy_Boss.h"
#include "Enemy_Truck.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	textureRED = App->textures->Load("Assets/EnemySpriteRec.png");
	textureGREEN = App->textures->Load("Assets/Guerrilla War Enemy Spritesheet1.png");
	textureBOMB = App->textures->Load("Assets/Guerrilla War Enemy Spritesheet.png");
	textureBOSS = App->textures->Load("Assets/Guerrilla War Boss Spritesheet.png");
	textureTRUCK = App->textures->Load("Assets/Guerrilla War Truck Spritesheet.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/explosion.wav");

	return true;
}

Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y, int movingbehaviour)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].movingbehaviour = movingbehaviour;
			ret = true;
			break;
		}
	}

	return ret;
}


void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			if (spawnQueue[i].y > App->render->camera.y - SPAWN_MARGIN) {


				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
			
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{ 
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.y > App->render->camera.y + App->render->camera.h + SPAWN_MARGIN || enemies[i]->position.y < -4050)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::RED:
					enemies[i] = new Enemy_Red(info.x, info.y, info.movingbehaviour);
					enemies[i]->texture = textureRED;
					break;
				case Enemy_Type::GREEN:
					enemies[i] = new Enemy_Green(info.x, info.y, info.movingbehaviour);
					enemies[i]->texture = textureGREEN;
					break;
				case Enemy_Type::BOMB:
					enemies[i] = new Enemy_Green_Bomb(info.x, info.y);
					enemies[i]->texture = textureBOMB;
					break;
				case Enemy_Type::BOSS:
					enemies[i] = new Enemy_Boss(info.x, info.y);
					enemies[i]->texture = textureBOSS;
					break;
				case Enemy_Type::TRUCK:
					enemies[i] = new Enemy_Truck(info.x, info.y);
					enemies[i]->texture = textureTRUCK;
					break;
			}
			
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			if (enemies[i]->deathcounter == 100) {
				delete enemies[i];
				enemies[i] = nullptr;
			}

			break;
		}
	}
}