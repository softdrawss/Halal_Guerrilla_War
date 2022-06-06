#ifndef __POWERUP_PRISONER__
#define __POWERUP_PRISONER__

#include "PowerUp.h"

class PU_Prisoner : public PowerUp
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	PU_Prisoner(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void OnCollision(Collider* c1, Collider* c2);

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	bool alive = true;
	int happy;
	int sad;

	Collider* colliderEnemy = nullptr;

	//animations for the enemy
	Animation help;
	Animation saved;
	Animation death;
	Animation* currentAnim = nullptr;
};


#endif // __ENEMY_RED__