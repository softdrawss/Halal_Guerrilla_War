#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class PowerUp
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	PowerUp(int x, int y);

	// Destructor
	virtual ~PowerUp();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	//booleans for dead enemiies
	bool dead = false;
	int deathcounter;

protected:
	// A ptr to the current animation
	Animation* prisonercurrentAnim = nullptr;
	Animation* weaponcurrentAnim = nullptr;
	Animation* currentDeathAnim = nullptr;

	// The powerup's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};
#endif // __POWERUP_H__