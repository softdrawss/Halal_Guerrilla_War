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


ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	textureRED = App->textures->Load("Assets/Guerrilla War Red Sprites.png");
	textureGREEN = App->textures->Load("Assets/Guerrilla War Enemy Spritesheet.png");
	textureBOMB = App->textures->Load("Assets/Guerrilla War Enemy Spritesheet.png");
	textureBOSS = App->textures->Load("Assets/Guerrilla War Boss Spritesheet.png");
	textureTRUCK = App->textures->Load("Assets/Guerrilla War Truck Spritesheet.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/explosion.wav");

	return true;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
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

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
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
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
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
				case ENEMY_TYPE::RED:
					enemies[i] = new Enemy_Red(info.x, info.y);
					enemies[i]->texture = textureRED;
					break;
				case ENEMY_TYPE::GREEN:
					enemies[i] = new Enemy_Green(info.x, info.y);
					enemies[i]->texture = textureGREEN;
					break;
				case ENEMY_TYPE::BOMB:
					enemies[i] = new Enemy_Green_Bomb(info.x, info.y);
					enemies[i]->texture = textureBOMB;
					break;
				case ENEMY_TYPE::BOSS:
					enemies[i] = new Enemy_Boss(info.x, info.y);
					enemies[i]->texture = textureBOSS;
					break;
				case ENEMY_TYPE::TRUCK:
					enemies[i] = new Enemy_Boss(info.x, info.y);
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
			uint deathEnemy = App->audio->LoadFx("Assets/gwar-198.wav");
			App->audio->PlayFx(deathEnemy, 0);
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}