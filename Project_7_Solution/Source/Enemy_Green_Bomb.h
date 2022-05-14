#ifndef __ENEMY_GREEN_BOMB_H__
#define __ENEMY_GREEN__BOMB_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Green_Bomb : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Green_Bomb(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	float speed = 0.05f;

	// The animations of each moment
	// The sprites used here are not the ones in the game
	Animation still;
	Animation attack;
};

#endif // __ENEMY_GREEN_H__
