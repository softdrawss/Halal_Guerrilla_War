#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5


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
		WATER,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		POWERUP,
		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);
	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;

	
	//SDL_Renderer renderer;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

