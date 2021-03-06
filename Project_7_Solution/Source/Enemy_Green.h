#ifndef __ENEMY_GREEN_H__
#define __ENEMY_GREEN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Green : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Green(int x, int y, int movingbehaviour);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//functions for the movement behaviours
	void godownshootgoup();
	void dontmove();
	void OnCollision(Collider* collider)override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path, pathup, pathdown;



	int waitforshoot;
	bool jajabool;


	// The animations of each moment
	// The sprites used here are not the ones in the game
	Animation Eup, Edown, Eleft, Eright, Eupleft, Eupright, Edownleft, Edownright;
	Animation uEwalkup, uEwalkdown, uEwalkleft, uEwalkright, uEwalkupleft, uEwalkupright, uEwalkdownleft, uEwalkdownright;
	Animation bEwalkup, bEwalkdown, bEwalkleft, bEwalkright, bEwalkupleft, bEwalkupright, bEwalkdownleft, bEwalkdownright;
	Animation deathanim, iddledeathanim;

};

#endif // __ENEMY_GREEN_H__