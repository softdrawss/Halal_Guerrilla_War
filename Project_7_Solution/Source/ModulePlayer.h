#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	//the texture of the weapon
	SDL_Texture* weapon_texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimationtorso = nullptr;
	Animation* currentAnimationlegs = nullptr;
	Animation* weapon = nullptr;

	// all animations of movement

	Animation torsoup, torsodown, torsoright, torsoleft, torsoupright, torsoupleft, torsodownright, torsodownleft;
	Animation legsup, legsdown, legsleft, legsright, legsupright, legsupleft, legsdownright, legsdownleft;
	Animation torsoiddleAnim, legsiddleAnim;
	Animation weapon_up, weapon_down, weapon_right, weapon_left, weapon_upright, weapon_upleft, weapon_downright, weapon_downleft;
	Animation weapon_up_shot, weapon_down_shot, weapon_right_shot, weapon_left_shot, weapon_upright_shot, weapon_upleft_shot, weapon_downright_shot, weapon_downleft_shot;

	Animation normalweapon_up, normalweapon_down, normalweapon_right, normalweapon_left, normalweapon_upright, normalweapon_upleft, normalweapon_downright, normalweapon_downleft;
	Animation normalweapon_up_shot, normalweapon_down_shot, normalweapon_right_shot, normalweapon_left_shot, normalweapon_upright_shot, normalweapon_upleft_shot, normalweapon_downright_shot, normalweapon_downleft_shot;

	Animation heavyweapon_up, heavyweapon_down, heavyweapon_right, heavyweapon_left, heavyweapon_upright, heavyweapon_upleft, heavyweapon_downright, heavyweapon_downleft;
	Animation heavyweapon_up_shot, heavyweapon_down_shot, heavyweapon_right_shot, heavyweapon_left_shot, heavyweapon_upright_shot, heavyweapon_upleft_shot, heavyweapon_downright_shot, heavyweapon_downleft_shot;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool dead = false;
	bool facer, facel, faceu, faced, faceur, faceul, facedr, facedl;
	bool normalweapon;
	bool heavyweapon;



	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

};

#endif //!__MODULE_PLAYER_H__