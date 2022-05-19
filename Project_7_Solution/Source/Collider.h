#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;

class Circle {
	int cX, cY, radius;
};

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		DESTROYABLE_WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		POWERUP,
		ATTACK,
		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);
	Collider(int centreX, int centreY, int radius, Type type, Module* listener = nullptr);
	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	//Variables
	SDL_Rect rect;

	
	//SDL_Renderer renderer;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};


#endif // !__COLLIDER_H__

