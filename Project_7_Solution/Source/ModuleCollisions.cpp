#include "ModuleCollisions.h"

#include "Application.h"
#include "Enemy.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::POWERUP] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::POWERUP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ATTACK] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ATTACK] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ATTACK] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ATTACK] = false;

	matrix[Collider::Type::POWERUP][Collider::Type::WALL] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::POWERUP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::POWERUP] = false;
	matrix[Collider::Type::POWERUP][Collider::Type::ATTACK] = false;

	matrix[Collider::Type::ATTACK][Collider::Type::WALL] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::ATTACK] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::POWERUP] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->Intersects(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->listener)
					c1->listener->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->listener)
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_X] == KEY_DOWN)
		debug = !debug;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::DESTROYABLE_WALL: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::ATTACK:
			//App->render->DrawQuad(colliders[i]->rect, 106, 90, 205, alpha);
			//App->render->DrawCircle(App->player->position.x, App->player->position.y, 200, App->render->renderer, 0, 0, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

Collider* ModuleCollisions::AddSpecialCollider(int centreX, int centreY, int radius, Collider::Type type, Module* listener) {
	Collider* circle = nullptr;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (enemyColliders[i] == nullptr)
		{
			circle = enemyColliders[i] = new Collider(centreX, centreY, radius, type, listener);
			break;
		}
	}

	return circle;
}


