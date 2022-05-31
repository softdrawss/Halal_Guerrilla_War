#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y, int movingbehaviour);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	//virtual void Attack();
	virtual void Attack();
	virtual void Attackdown();


	//function to know ehre is the player so it can face it
	void facingtoplayer();
	void direction();

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

	//speed of the enemies
	int speed;

	iPoint distance;
	//center of the line to aim to the player
	int cx, cy;
	// position of the player as the end of the line
	int rx, ry;
	//degress respect to the player
	float angle, degrees;
	// direction
	bool up, down, left, right, upright, upleft, downright, downleft;

	

	int delay1, bulletscounter;

	int movingbehaviour;

	bool ismoving;

	//booleans for dead enemiies
	bool dead;
	int deathcounter;

protected:
	// A ptr to the current animation
	Animation* redcurrentAnim = nullptr;
	Animation* greencurrentAnim = nullptr;
	Animation* greenlegscurrentAnim = nullptr;
	Animation* greentorsocurrentAnim = nullptr;
	Animation* currentdeathanim = nullptr;


	// The enemy's collider
	Collider* collider = nullptr;
	Collider* attack = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__