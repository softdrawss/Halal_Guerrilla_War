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
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

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
	Animation* currentdeathanim = nullptr;

	// all animations of movement

	Animation torsoup, torsodown, torsoright, torsoleft, torsoupright, torsoupleft, torsodownright, torsodownleft;
	Animation legsup, legsdown, legsleft, legsright, legsupright, legsupleft, legsdownright, legsdownleft;
	Animation torsoiddleAnim, legsiddleAnim, wateriddleAnim;
	Animation weapon_up, weapon_down, weapon_right, weapon_left, weapon_upright, weapon_upleft, weapon_downright, weapon_downleft;
	Animation weapon_up_shot, weapon_down_shot, weapon_right_shot, weapon_left_shot, weapon_upright_shot, weapon_upleft_shot, weapon_downright_shot, weapon_downleft_shot;

	Animation normalweapon_up, normalweapon_down, normalweapon_right, normalweapon_left, normalweapon_upright, normalweapon_upleft, normalweapon_downright, normalweapon_downleft;
	Animation normalweapon_up_shot, normalweapon_down_shot, normalweapon_right_shot, normalweapon_left_shot, normalweapon_upright_shot, normalweapon_upleft_shot, normalweapon_downright_shot, normalweapon_downleft_shot;

	Animation heavyweapon_up, heavyweapon_down, heavyweapon_right, heavyweapon_left, heavyweapon_upright, heavyweapon_upleft, heavyweapon_downright, heavyweapon_downleft;
	Animation heavyweapon_up_shot, heavyweapon_down_shot, heavyweapon_right_shot, heavyweapon_left_shot, heavyweapon_upright_shot, heavyweapon_upleft_shot, heavyweapon_downright_shot, heavyweapon_downleft_shot;

	Animation water;

	Animation deathanim, iddledeathanim;

	// The player's collider
	Collider* collider = nullptr;
	Collider* collider1 = nullptr;

	// A flag to detect when the player has been killed aswell as a counter to the death;
	bool dead = false, winner = false;
	int deathcounter;

	//booleans to know the direction the player is facing
	bool facer, facel, faceu, faced, faceur, faceul, facedr, facedl, waterP;
	//booleans for the powerups
	bool normalweapon;
	bool heavyweapon;

	// lives of the player
	int lives = 0;
	
	// Font score index
	uint score = 000;
	int granades = 0;
	int bullets = 0; 
	int credits = 0;

	int scoreFont = -1;
	int weaponsFont = -1;
	int playerFont = -1;
	char scoreText[10] = { "\0" };
	char livesText[10] = { "\0" };
	char granadesText[10] = { "\0" };
	char bulletsText[10] = { "\0" };
	char creditsText[10] = { "\0" };
};

#endif //!__MODULE_PLAYER_H__