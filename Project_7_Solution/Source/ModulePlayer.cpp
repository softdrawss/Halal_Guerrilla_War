#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"

#include <stdio.h>
#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	//iddle animation
	torsoiddleAnim.PushBack({ 4,4,26,31 });
	legsiddleAnim.PushBack({ 169, 0, 23, 31 });
	wateriddleAnim.PushBack({ 363, 23, 32, 32 });

	// walk forward animation
	legsup.PushBack({ 0, 33, 32, 32 });
	legsup.PushBack({ 33, 33, 32, 32 });
	legsup.PushBack({ 65, 33, 32, 32 });
	legsup.PushBack({ 97, 33,32, 32 });
	legsup.PushBack({ 130, 34, 32, 32 });
	legsup.PushBack({ 97, 33,32, 32 });
	legsup.PushBack({ 65, 33, 32, 32 });
	legsup.PushBack({ 33, 33, 32, 32 });
	legsup.speed = 0.1f;

	torsoup.PushBack({ 0,1,32,32 });
	torsoup.PushBack({ 33,1,32,32 });
	torsoup.PushBack({ 65,1,32,32 });
	torsoup.PushBack({ 97,1,32,32 });
	torsoup.PushBack({ 130,1,32,32 });
	torsoup.PushBack({ 97,1,32,32 });
	torsoup.PushBack({ 65,1,32,32 });
	torsoup.PushBack({ 33,1,32,32 });
	torsoup.speed = 0.1f;

	//walk down animation

	legsdown.PushBack({ 1,276,32,32 });
	legsdown.PushBack({ 33,276,32,32 });
	legsdown.PushBack({ 65,276,32,32 });
	legsdown.PushBack({ 97,276,32,32 });
	legsdown.PushBack({ 129,276,32,32 });
	legsdown.PushBack({ 97,276,32,32 });
	legsdown.PushBack({ 65,276,32,32 });
	legsdown.PushBack({ 33,276,32,32 });
	legsdown.speed = 0.1f;

	torsodown.PushBack({ 1,244,32,32 });
	torsodown.PushBack({ 33,244,32,32 });
	torsodown.PushBack({ 65,244,32,32 });
	torsodown.PushBack({ 97,244,32,32 });
	torsodown.PushBack({ 129,244,32,32 });
	torsodown.PushBack({ 97,244,32,32 });
	torsodown.PushBack({ 65,244,32,32 });
	torsodown.PushBack({ 33,244,32,32 });
	torsodown.speed = 0.1f;

	//walk left animation

	legsleft.PushBack({ 4,401,32,32 });
	legsleft.PushBack({ 36,401,32,32 });
	legsleft.PushBack({ 68,401,32,32 });
	legsleft.PushBack({ 100,401,32,32 });
	legsleft.PushBack({ 132,401,32,32 });
	legsleft.PushBack({ 100,401,32,32 });
	legsleft.PushBack({ 68,401,32,32 });
	legsleft.PushBack({ 36,401,32,32 });
	legsleft.speed = 0.1f;

	torsoleft.PushBack({ 4, 369, 32, 32 });
	torsoleft.PushBack({ 36, 369, 32, 32 });
	torsoleft.PushBack({ 68, 369, 32, 32 });
	torsoleft.PushBack({ 100, 369, 32, 32 });
	torsoleft.PushBack({ 132, 369, 32, 32 });
	torsoleft.PushBack({ 100, 369, 32, 32 });
	torsoleft.PushBack({ 68, 369, 32, 32 });
	torsoleft.PushBack({ 36, 369, 32, 32 });
	torsoleft.speed = 0.1f;


	//walk right animation

	legsright.PushBack({ 2,155,32,29 });
	legsright.PushBack({ 34,155,32,29 });
	legsright.PushBack({ 66,155,32,29 });
	legsright.PushBack({ 98,155,32,29 });
	legsright.PushBack({ 130,155,32,29 });
	legsright.PushBack({ 98,155,32,29 });
	legsright.PushBack({ 66,155,32,29 });
	legsright.PushBack({ 34,155,32,29 });
	legsright.speed = 0.1f;

	torsoright.PushBack({ 2,123,32,32 });
	torsoright.PushBack({ 34,123,32,32 });
	torsoright.PushBack({ 66,123,32,32 });
	torsoright.PushBack({ 98,123,32,32 });
	torsoright.PushBack({ 130,123,32,32 });
	torsoright.PushBack({ 98,123,32,32 });
	torsoright.PushBack({ 66,123,32,32 });
	torsoright.PushBack({ 34,123,32,32 });
	torsoright.speed = 0.1f;

	//walk upright animation
	torsoupright.PushBack({ 2,62,32,32 });
	torsoupright.PushBack({ 34,62,32,32 });
	torsoupright.PushBack({ 66,62,32,32 });
	torsoupright.PushBack({ 98,62,32,32 });
	torsoupright.PushBack({ 130,62,32,32 });
	torsoupright.PushBack({ 98,62,32,32 });
	torsoupright.PushBack({ 66,62,32,32 });
	torsoupright.PushBack({ 34,62,32,32 });
	torsoupright.speed = 0.1f;

	legsupright.PushBack({ 2,94,32,32 });
	legsupright.PushBack({ 34,94,32,32 });
	legsupright.PushBack({ 66,94,32,32 });
	legsupright.PushBack({ 98,94,32,32 });
	legsupright.PushBack({ 130,94,32,32 });
	legsupright.PushBack({ 98,94,32,32 });
	legsupright.PushBack({ 66,94,32,32 });
	legsupright.PushBack({ 34,94,32,32 });
	legsupright.speed = 0.1f;


	//walk upleft aimation
	torsoupleft.PushBack({ 4,429,32,32 });
	torsoupleft.PushBack({ 36,429,32,32 });
	torsoupleft.PushBack({ 68,429,32,32 });
	torsoupleft.PushBack({ 100,429,32,32 });
	torsoupleft.PushBack({ 132,429,32,32 });
	torsoupleft.PushBack({ 100,429,32,32 });
	torsoupleft.PushBack({ 68,429,32,32 });
	torsoupleft.PushBack({ 36,429,32,32 });
	torsoupleft.speed = 0.1f;

	legsupleft.PushBack({ 4,461,32,32 });
	legsupleft.PushBack({ 36,461,32,32 });
	legsupleft.PushBack({ 68,461,32,32 });
	legsupleft.PushBack({ 100,461,32,32 });
	legsupleft.PushBack({ 132,461,32,32 });
	legsupleft.PushBack({ 100,461,32,32 });
	legsupleft.PushBack({ 68,461,32,32 });
	legsupleft.PushBack({ 36,461,32,32 });
	legsupleft.speed = 0.1f;

	//walk downright animation
	torsodownright.PushBack({ 2,181,32,32 });
	torsodownright.PushBack({ 34,181,32,32 });
	torsodownright.PushBack({ 66,181,32,32 });
	torsodownright.PushBack({ 98,181,32,32 });
	torsodownright.PushBack({ 130,181,32,32 });
	torsodownright.PushBack({ 98,181,32,32 });
	torsodownright.PushBack({ 66,181,32,32 });
	torsodownright.PushBack({ 34,181,32,32 });
	torsodownright.speed = 0.1f;

	legsdownright.PushBack({ 2,213,32,32 });
	legsdownright.PushBack({ 34,213,32,32 });
	legsdownright.PushBack({ 66,213,32,32 });
	legsdownright.PushBack({ 98,213,32,32 });
	legsdownright.PushBack({ 130,213,32,32 });
	legsdownright.PushBack({ 98,213,32,32 });
	legsdownright.PushBack({ 66,213,32,32 });
	legsdownright.PushBack({ 34,213,32,32 });
	legsdownright.speed = 0.1f;

	//walk downleft aimation
	torsodownleft.PushBack({ 1,306,32,32 });
	torsodownleft.PushBack({ 33,306,32,32 });
	torsodownleft.PushBack({ 65,306,32,32 });
	torsodownleft.PushBack({ 97,306,32,32 });
	torsodownleft.PushBack({ 129,306,32,32 });
	torsodownleft.PushBack({ 97,306,32,32 });
	torsodownleft.PushBack({ 65,306,32,32 });
	torsodownleft.PushBack({ 33,306,32,32 });
	torsodownleft.speed = 0.1f;

	legsdownleft.PushBack({ 1,338,32,32 });
	legsdownleft.PushBack({ 33,338,32,32 });
	legsdownleft.PushBack({ 65,338,32,32 });
	legsdownleft.PushBack({ 97,338,32,32 });
	legsdownleft.PushBack({ 129,338,32,32 });
	legsdownleft.PushBack({ 97,338,32,32 });
	legsdownleft.PushBack({ 65,338,32,32 });
	legsdownleft.PushBack({ 33,338,32,32 });
	legsdownleft.speed = 0.1f;

	//animation water
	water.PushBack({ 363, 23, 32, 32 });
	water.PushBack({ 396, 23, 32, 32 });
	water.PushBack({ 431, 23, 32, 32 });
	water.PushBack({ 460, 23, 32, 32 });

	//normalweapon up
	normalweapon_up.PushBack({ 17,27,5,16 });
	//weaponup.PushBack({ 18,40,13,24 });

	//weapon down
	normalweapon_down.PushBack({ 170,10,6,24 });
	//weapon right
	normalweapon_right.PushBack({ 73,20,23,16 });
	//weapon left
	normalweapon_left.PushBack({ 238,38,18,13 });
	//weapon upright
	normalweapon_upright.PushBack({ 33,24,15,15 });
	//weapon upleft
	normalweapon_upleft.PushBack({ 274,32,14,14 });
	//weapondownright
	normalweapon_downright.PushBack({ 129,13,19,23 });
	//weapondownleft
	normalweapon_downleft.PushBack({ 204,11,15,20 });

	normalweapon_up_shot.PushBack({ 14,51,13,24 });
	normalweapon_up_shot.PushBack({ 17,27,5,16 });
	normalweapon_up_shot.speed = 0.1f;
	//weapon down shot
	normalweapon_down_shot.PushBack({ 164,46,17,37 });
	//weapon left shot
	normalweapon_left_shot.PushBack({ 229,66,27,17 });
	//weapon right shot
	normalweapon_right_shot.PushBack({ 72,50,32,22 });
	//weapon upright shot
	normalweapon_upright_shot.PushBack({ 14,51,13,24 });
	//weapon upleft shot
	normalweapon_upleft_shot.PushBack({ 32,49,22,23 });
	//weapon downright shot
	normalweapon_downright_shot.PushBack({ 128,50,27,31 });
	//weapon downleft shot
	normalweapon_downleft_shot.PushBack({ 195,49,26,24 });

	//heavyweapon up
	heavyweapon_up.PushBack({ 17,83,8,24 });
	//heavyweapon down
	heavyweapon_down.PushBack({ 168,85,8,30 });
	//heavyweapon right
	heavyweapon_right.PushBack({ 73,91,30,14 });
	//heavyweapon left
	heavyweapon_left.PushBack({ 233,100,23,12 });
	//heavyweapon upright
	heavyweapon_upright.PushBack({ 33,83,20,21 });
	//heavyweapon upleft
	heavyweapon_upleft.PushBack({ 270,92,16,19 });
	//heavyweapon downright
	heavyweapon_downright.PushBack({ 129,88,24,28 });
	//heavyweapon downleft
	heavyweapon_downleft.PushBack({ 198,86,25,25 });


	//heavyweapon up shot
	heavyweapon_up_shot.PushBack({ 11,107,14,32 });
	heavyweapon_up.PushBack({ 17,83,8,24 });
	heavyweapon_up_shot.speed = 0.1f;
	//heavyweapon down shot
	heavyweapon_down_shot.PushBack({ 161,121,25,38 });
	//heavyweapon right shot
	heavyweapon_right_shot.PushBack({ 72,121,34,21 });
	//heavyweapon left shot
	heavyweapon_left_shot.PushBack({ 228,128,28,18 });
	//heavyweapon upright shot
	heavyweapon_upright_shot.PushBack({ 32,109,27,28 });
	//heavyweapon upleft shot
	heavyweapon_upleft_shot.PushBack({ 165,117,24,27 });
	//heavyweapon downright shot
	heavyweapon_downright_shot.PushBack({ 128,127,31,33 });
	//heavyweapon downleft shot
	heavyweapon_downleft_shot.PushBack({ 189,126,33,32 });

	//pushbacks for the player death animations

	deathanim.PushBack({ 354,209,32,64 });
	deathanim.PushBack({ 388,209,32,64 });
	deathanim.PushBack({ 420,209,32,64 });
	deathanim.PushBack({ 451,209,32,64 });
	deathanim.PushBack({ 480,209,32,64 });
	deathanim.PushBack({ 351,272,32,64 });
	deathanim.PushBack({ 382,272,32,64 });
	deathanim.PushBack({ 447,272,32,64 });
	deathanim.PushBack({ 479,272,32,64 });
	deathanim.speed = 0.1f;
	deathanim.loop = false;

	iddledeathanim.PushBack({ 354,209,32,64 });

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	position.x = 250;
	position.y = 300;

	bool ret = true;
	normalweapon = true;
	heavyweapon = false;
	dead = false;
	lives = 3;
	granades = 50;
	bullets = 0;
	deathcounter = 0;

	texture = App->textures->Load("Assets/Guerrilla War Player 1 Spritesheet OK.png");
	weapon_texture = App->textures->Load("Assets/Guerrilla War Weapon Spritesheet1.png");
	currentAnimationlegs = &legsup;
	currentAnimationtorso = &torsoup;
	currentdeathanim = &iddledeathanim;
	weapon = &normalweapon_up;
	faceu = true;
	faced = false;
	facer = false;
	facel = false;
	faceur = false;
	faceul = false;
	facedr = false;
	facedl = false;

	//add collider player
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 64 }, Collider::Type::PLAYER, this);


	// Font UI
	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.@'?&- " };
	scoreFont = App->fonts->Load("Assets/ui_font5.png", lookupTable, 1);
	
	// Font Images for Weapons and Granades
	char livesTable[] = { "BG 1" };
	weaponsFont = App->fonts->Load("Assets/ui_font4.png", livesTable, 1);

	return ret;

}

Update_Status ModulePlayer::Update()
{
	//Reset the currentAnimation back to idle before updating

	legsiddleAnim.frames[0] = currentAnimationlegs->frames[currentAnimationlegs->GetCurrentFrameint()];
	torsoiddleAnim.frames[0] = currentAnimationtorso->frames[currentAnimationtorso->GetCurrentFrameint()];

	currentAnimationlegs = &legsiddleAnim;
	currentAnimationtorso = &torsoiddleAnim;

	if (waterP = false) {
		//up	
		if (faceu == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationlegs = &legsupleft;
			currentAnimationtorso = &torsoup;
			position.x += speed;
			position.y += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationlegs = &legsupright;
			currentAnimationtorso = &torsoup;
			position.x -= speed;
			position.y += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationlegs = &legsupright;
			currentAnimationtorso = &torsoup;
			position.x += speed;
			position.y -= speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationlegs = &legsupleft;
			currentAnimationtorso = &torsoup;
			position.x -= speed;
			position.y -= speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {
			currentAnimationtorso = &torsoup;
			currentAnimationlegs = &legsup;
			position.y -= speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			currentAnimationlegs = &legsup;
			currentAnimationtorso = &torsoup;
			position.y += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
			currentAnimationlegs = &legsright;
			currentAnimationtorso = &torsoup;
			position.x += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
			currentAnimationlegs = &legsleft;
			currentAnimationtorso = &torsoup;
			position.x -= speed;
		}
		//down
		else if (faced == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsdownleft;
			position.y -= speed;
			position.x += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsdownright;
			position.y -= speed;
			position.x -= speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsdownleft;
			position.y += speed;
			position.x -= speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsdownright;
			position.y += speed;
			position.x += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsdown;
			position.y += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsdown;
			position.y -= speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsright;
			position.x += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &legsleft;
			position.x -= speed;
		}


		//right
		else if (facer == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsupright;
			position.y += speed;
			position.x -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsdownright;
			position.y += speed;
			position.x += speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsupright;
			position.y -= speed;
			position.x += speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsdownright;
			position.y -= speed;
			position.x -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsright;
			position.x += speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsright;
			position.x -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsup;
			position.y -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &legsdown;
			position.y += speed;
		}


		//left
		else if (facel == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsdownleft;
			position.y += speed;
			position.x -= speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsupleft;
			position.y += speed;
			position.x += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsdownleft;
			position.y -= speed;
			position.x += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsupleft;
			position.y -= speed;
			position.x -= speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsleft;
			position.x -= speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsleft;
			position.x += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsdown;
			position.y += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &legsup;
			position.y -= speed;
		}


		//upright
		else if (faceur == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsdownright;
			position.x -= speed;
			position.y -= speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsupright;
			position.x += speed;
			position.y -= speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsupright;
			position.x -= speed;
			position.y += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsdownright;
			position.x += speed;
			position.y += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsup;
			position.y -= speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsup;
			position.y += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsright;
			position.x += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &legsright;
			position.x -= speed;
		}

		//upleft
		else if (faceul == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsupleft;
			position.x -= speed;
			position.y -= speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsupright;
			position.x += speed;
			position.y -= speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsdownleft;
			position.x -= speed;
			position.y += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsupleft;
			position.x += speed;
			position.y += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsup;
			position.y -= speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsup;
			position.y += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsleft;
			position.x += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &legsleft;
			position.x -= speed;
		}


		//downright
		else if (facedr == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsdownright;
			position.x -= speed;
			position.y -= speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsupright;
			position.x += speed;
			position.y -= speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsupright;
			position.x -= speed;
			position.y += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsdownright;
			position.x += speed;
			position.y += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsdown;
			position.y -= speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsdown;
			position.y += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsright;
			position.x += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &legsright;
			position.x -= speed;
		}

		//down left
		else if (facedl == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsupleft;
			position.x -= speed;
			position.y -= speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsdownleft;
			position.x += speed;
			position.y -= speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsdownleft;
			position.x -= speed;
			position.y += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsupleft;
			position.x += speed;
			position.y += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsdown;
			position.y -= speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsdown;
			position.y += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsleft;
			position.x += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &legsleft;
			position.x -= speed;
		}


		if (normalweapon == true && heavyweapon == false) {
			//look up
			if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				//App->particles->AddParticle(App->particles->normal_up_shot, position.x +20, position.y+20, Collider::Type::PLAYER_SHOT);
				currentAnimationtorso = &torsoup;
				weapon = &normalweapon_up;
				faceu = true;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look down
			if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodown;
				weapon = &normalweapon_down;
				faceu = false;
				faced = true;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look right
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoright;
				weapon = &normalweapon_right;
				faceu = false;
				faced = false;
				facer = true;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look left
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoleft;
				weapon = &normalweapon_left;
				faceu = false;
				faced = false;
				facer = false;
				facel = true;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupright;
				weapon = &normalweapon_upright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = true;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupleft;
				weapon = &normalweapon_upleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = true;
				facedr = false;
				facedl = false;
			}
			//look downright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownright;
				weapon = &normalweapon_downright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = true;
				facedl = false;
			}
			//look downleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownleft;
				weapon = &normalweapon_downleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = true;
			}
			//shots

			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
			{
				uint shoot = App->audio->LoadFx("Assets/gwar-137.wav");
				if (faceu == true) {
					App->particles->AddParticle(App->particles->normal_up_shot, position.x + 22, position.y + 4, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (faced == true) {
					App->particles->AddParticle(App->particles->normal_down_shot, position.x + 8, position.y + 35, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facer == true) {
					App->particles->AddParticle(App->particles->normal_hr_shot, position.x + 20, position.y + 24, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facel == true) {
					App->particles->AddParticle(App->particles->normal_hl_shot, position.x - 4, position.y + 21, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (faceur == true) {
					App->particles->AddParticle(App->particles->normal_ur_shot, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (faceul == true) {
					App->particles->AddParticle(App->particles->normal_ul_shot, position.x + 6, position.y + 10, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facedr == true) {
					App->particles->AddParticle(App->particles->normal_dr_shot, position.x + 18, position.y + 35, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facedl == true) {
					App->particles->AddParticle(App->particles->normal_dl_shot, position.x + 2, position.y + 26, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
			}
		}
		else if (heavyweapon == true && normalweapon == false) {
			//look up
			if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				//App->particles->AddParticle(App->particles->normal_up_shot, position.x +20, position.y+20, Collider::Type::PLAYER_SHOT);
				currentAnimationtorso = &torsoup;
				weapon = &heavyweapon_up;
				faceu = true;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look down
			if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodown;
				weapon = &heavyweapon_down;
				faceu = false;
				faced = true;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look right
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoright;
				weapon = &heavyweapon_right;
				faceu = false;
				faced = false;
				facer = true;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look left
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoleft;
				weapon = &heavyweapon_left;
				faceu = false;
				faced = false;
				facer = false;
				facel = true;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupright;
				weapon = &heavyweapon_upright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = true;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupleft;
				weapon = &heavyweapon_upleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = true;
				facedr = false;
				facedl = false;
			}
			//look downright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownright;
				weapon = &heavyweapon_downright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = true;
				facedl = false;
			}
			//look downleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownleft;
				weapon = &heavyweapon_downleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = true;
			}

			//shots
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
			{
				uint shootheavy = App->audio->LoadFx("Assets/gwar-137.wav");
				if (faceu == true) {
					App->particles->AddParticle(App->particles->normal_up_shot, position.x + 22, position.y + 4, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shootheavy, 0);
				}
				else if (faced == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_down_shot, position.x + 8, position.y + 35, Collider::Type::PLAYER_SHOT);
				}
				else if (facer == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_hr_shot, position.x + 20, position.y + 24, Collider::Type::PLAYER_SHOT);
				}
				else if (facel == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_hl_shot, position.x - 4, position.y + 21, Collider::Type::PLAYER_SHOT);
				}
				else if (faceur == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_ur_shot, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
				}
				else if (faceul == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_ul_shot, position.x + 6, position.y + 10, Collider::Type::PLAYER_SHOT);
				}
				else if (facedr == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_dr_shot, position.x + 18, position.y + 35, Collider::Type::PLAYER_SHOT);
				}
				else if (facedl == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_dl_shot, position.x + 2, position.y + 26, Collider::Type::PLAYER_SHOT);
				}
			}
		}
	}
	else {
		wateriddleAnim.frames[0] = currentAnimationlegs->frames[currentAnimationlegs->GetCurrentFrameint()];
		currentAnimationlegs = &wateriddleAnim;
		//up	
		if (faceu == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationlegs = &water;
			currentAnimationtorso = &torsoup;
			position.x += speed;
			position.y += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationlegs = &water;
			currentAnimationtorso = &torsoup;
			position.x -= speed;
			position.y += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationlegs = &water;
			currentAnimationtorso = &torsoup;
			position.x += speed;
			position.y -= speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationlegs = &water;
			currentAnimationtorso = &torsoup;
			position.x -= speed;
			position.y -= speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {
			currentAnimationtorso = &torsoup;
			currentAnimationlegs = &water;
			position.y -= speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			currentAnimationlegs = &water;
			currentAnimationtorso = &torsoup;
			position.y += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
			currentAnimationlegs = &water;
			currentAnimationtorso = &torsoup;
			position.x += speed;
		}
		else if (faceu == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
			currentAnimationlegs = &water;
			currentAnimationtorso = &torsoup;
			position.x -= speed;
		}
		//down
		else if (faced == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.y -= speed;
			position.x += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.y -= speed;
			position.x -= speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.y += speed;
			position.x -= speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.y += speed;
			position.x += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.y += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.y -= speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.x += speed;
		}
		else if (faced == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsodown;
			currentAnimationlegs = &water;
			position.x -= speed;
		}


		//right
		else if (facer == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.y += speed;
			position.x -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.y += speed;
			position.x += speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.y -= speed;
			position.x += speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.y -= speed;
			position.x -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.x += speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.x -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.y -= speed;
		}
		else if (facer == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoright;
			currentAnimationlegs = &water;
			position.y += speed;
		}


		//left
		else if (facel == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.y += speed;
			position.x -= speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.y += speed;
			position.x += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.y -= speed;
			position.x += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.y -= speed;
			position.x -= speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.x -= speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.x += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.y += speed;
		}
		else if (facel == true && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
		{
			currentAnimationtorso = &torsoleft;
			currentAnimationlegs = &water;
			position.y -= speed;
		}


		//upright
		else if (faceur == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y -= speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y -= speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.y -= speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.y += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.x += speed;
		}
		else if (faceur == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsoupright;
			currentAnimationlegs = &water;
			position.x -= speed;
		}

		//upleft
		else if (faceul == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y -= speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y -= speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.y -= speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.y += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.x += speed;
		}
		else if (faceul == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsoupleft;
			currentAnimationlegs = &water;
			position.x -= speed;
		}


		//downright
		else if (facedr == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y -= speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y -= speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.y -= speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.y += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.x += speed;
		}
		else if (facedr == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsodownright;
			currentAnimationlegs = &water;
			position.x -= speed;
		}

		//down left
		else if (facedl == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y -= speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y -= speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.x -= speed;
			position.y += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.x += speed;
			position.y += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_W])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.y -= speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_S])
		{
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.y += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_D]) {
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.x += speed;
		}
		else if (facedl == true && App->input->keys[SDL_SCANCODE_A]) {
			currentAnimationtorso = &torsodownleft;
			currentAnimationlegs = &water;
			position.x -= speed;
		}


		if (normalweapon == true && heavyweapon == false) {
			//look up
			if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				//App->particles->AddParticle(App->particles->normal_up_shot, position.x +20, position.y+20, Collider::Type::PLAYER_SHOT);
				currentAnimationtorso = &torsoup;
				weapon = &normalweapon_up;
				faceu = true;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look down
			if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodown;
				weapon = &normalweapon_down;
				faceu = false;
				faced = true;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look right
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoright;
				weapon = &normalweapon_right;
				faceu = false;
				faced = false;
				facer = true;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look left
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoleft;
				weapon = &normalweapon_left;
				faceu = false;
				faced = false;
				facer = false;
				facel = true;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupright;
				weapon = &normalweapon_upright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = true;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupleft;
				weapon = &normalweapon_upleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = true;
				facedr = false;
				facedl = false;
			}
			//look downright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownright;
				weapon = &normalweapon_downright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = true;
				facedl = false;
			}
			//look downleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownleft;
				weapon = &normalweapon_downleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = true;
			}
			//shots

			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
			{
				uint shoot = App->audio->LoadFx("Assets/gwar-137.wav");
				if (faceu == true) {
					App->particles->AddParticle(App->particles->normal_up_shot, position.x + 22, position.y + 4, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (faced == true) {
					App->particles->AddParticle(App->particles->normal_down_shot, position.x + 8, position.y + 35, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facer == true) {
					App->particles->AddParticle(App->particles->normal_hr_shot, position.x + 20, position.y + 24, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facel == true) {
					App->particles->AddParticle(App->particles->normal_hl_shot, position.x - 4, position.y + 21, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (faceur == true) {
					App->particles->AddParticle(App->particles->normal_ur_shot, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (faceul == true) {
					App->particles->AddParticle(App->particles->normal_ul_shot, position.x + 6, position.y + 10, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facedr == true) {
					App->particles->AddParticle(App->particles->normal_dr_shot, position.x + 18, position.y + 35, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
				else if (facedl == true) {
					App->particles->AddParticle(App->particles->normal_dl_shot, position.x + 2, position.y + 26, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shoot, 0);
				}
			}
		}
		else if (heavyweapon == true && normalweapon == false) {
			//look up
			if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				//App->particles->AddParticle(App->particles->normal_up_shot, position.x +20, position.y+20, Collider::Type::PLAYER_SHOT);
				currentAnimationtorso = &torsoup;
				weapon = &heavyweapon_up;
				faceu = true;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look down
			if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodown;
				weapon = &heavyweapon_down;
				faceu = false;
				faced = true;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look right
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoright;
				weapon = &heavyweapon_right;
				faceu = false;
				faced = false;
				facer = true;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}

			//look left
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoleft;
				weapon = &heavyweapon_left;
				faceu = false;
				faced = false;
				facer = false;
				facel = true;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupright;
				weapon = &heavyweapon_upright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = true;
				faceul = false;
				facedr = false;
				facedl = false;
			}
			//look upleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
			{
				currentAnimationtorso = &torsoupleft;
				weapon = &heavyweapon_upleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = true;
				facedr = false;
				facedl = false;
			}
			//look downright
			if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownright;
				weapon = &heavyweapon_downright;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = true;
				facedl = false;
			}
			//look downleft
			if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN && App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
			{
				currentAnimationtorso = &torsodownleft;
				weapon = &heavyweapon_downleft;
				faceu = false;
				faced = false;
				facer = false;
				facel = false;
				faceur = false;
				faceul = false;
				facedr = false;
				facedl = true;
			}

			//shots
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
			{
				uint shootheavy = App->audio->LoadFx("Assets/gwar-137.wav");
				if (faceu == true) {
					App->particles->AddParticle(App->particles->normal_up_shot, position.x + 22, position.y + 4, Collider::Type::PLAYER_SHOT);
					App->audio->PlayFx(shootheavy, 0);
				}
				else if (faced == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_down_shot, position.x + 8, position.y + 35, Collider::Type::PLAYER_SHOT);
				}
				else if (facer == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_hr_shot, position.x + 20, position.y + 24, Collider::Type::PLAYER_SHOT);
				}
				else if (facel == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_hl_shot, position.x - 4, position.y + 21, Collider::Type::PLAYER_SHOT);
				}
				else if (faceur == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_ur_shot, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
				}
				else if (faceul == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_ul_shot, position.x + 6, position.y + 10, Collider::Type::PLAYER_SHOT);
				}
				else if (facedr == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_dr_shot, position.x + 18, position.y + 35, Collider::Type::PLAYER_SHOT);
				}
				else if (facedl == true) {
					App->audio->PlayFx(shootheavy, 0);
					App->particles->AddParticle(App->particles->normal_dl_shot, position.x + 2, position.y + 26, Collider::Type::PLAYER_SHOT);
				}
			}
		}
		/*if (!OnCollision(c1, c2)) {

		}*/
	}
	

	//instawin
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) {
		score = 30000;
		if (score > 30000) {
			score = 30000;

		}
	}

	//instakill
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN) {
		dead = true;
	}

	//exit the game with esc
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {

		return Update_Status::UPDATE_STOP;
	}

	//if dead
	if (dead == true) {
		score = 0;
		lives = 0;
		if (deathcounter >= 100) {
			int deathSound = App->audio->LoadFx("Assets/gwar-195.wav");
			App->audio->PlayFx(deathSound, 0);
			//Start();
			App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneIntro, 60);
		}
		currentdeathanim = &deathanim;
		++deathcounter;
	}

	if (lives == 0) {
		dead = true;
	}
	
	//set collider position
	collider->SetPos(position.x, position.y);

	//update the animations of the weapon, torso and legs adn death
	currentAnimationlegs->Update();
	currentAnimationtorso->Update();
	currentdeathanim->Update();
	weapon->Update();
	 
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!dead)
	{
		//render legs
		SDL_Rect rect2 = currentAnimationlegs->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y + 32, &rect2);
		//render weapon
		SDL_Rect rect3 = weapon->GetCurrentFrame();
		if (faceu == true) {
			App->render->Blit(weapon_texture, position.x + 21, position.y + 2, &rect3);
		}
		else if (faced == true) {
			App->render->Blit(weapon_texture, position.x + 7, position.y + 22, &rect3);
		}
		else if (facel == true) {
			App->render->Blit(weapon_texture, position.x - 6, position.y + 20, &rect3);
		}
		else if (faceur == true) {
			App->render->Blit(weapon_texture, position.x + 19, position.y + 12, &rect3);
		}
		else if (faceul == true) {
			App->render->Blit(weapon_texture, position.x, position.y + 4, &rect3);
		}
		else if (facedr == true) {
			App->render->Blit(weapon_texture, position.x + 7, position.y + 22, &rect3);
		}

		//render torso
		SDL_Rect rect1 = currentAnimationtorso->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect1);

		if (facedl == true) {
			App->render->Blit(weapon_texture, position.x, position.y + 22, &rect3);
		}
		else if (facer == true) {
			App->render->Blit(weapon_texture, position.x + 8, position.y + 22, &rect3);
		}
	}

	//deth anim
	if (dead == true) {
		SDL_Rect rect4 = currentdeathanim->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect4);
	}

	// Draw UI (variables) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(livesText, 10, "%d", lives);
	sprintf_s(granadesText, 10, "%2d", granades);
	sprintf_s(bulletsText, 10, "%2d", bullets);
	sprintf_s(creditsText, 10, "%d", credits);

	// Text of the screen
	// Highscore of the level (if you kill all the enemies and save the prisoners)
	App->fonts->BlitText(130, 75, scoreFont, "HI");
	App->fonts->BlitText(250, 75, scoreFont, "30000");

	// Player 1 --> Available
	App->fonts->BlitText(83, 85, scoreFont, "1 UP");
	App->fonts->BlitText(75, 95, scoreFont, scoreText);

	// Player 2 --> Not available
	App->fonts->BlitText(290, 85, scoreFont, "2 UP");
	App->fonts->BlitText(330, 95, scoreFont, "0");

	// Weapons
	App->fonts->BlitText(20, 150, weaponsFont, "G");
	App->fonts->BlitText(20, 170, scoreFont, granadesText);

	App->fonts->BlitText(20, 180, weaponsFont, "B");
	App->fonts->BlitText(20, 200, scoreFont, bulletsText);


	// Lives
	if (lives == 2) {
		App->fonts->BlitText(18, 450, weaponsFont, "1");
	}if (lives == 3) {
		App->fonts->BlitText(18, 450, weaponsFont, "1");
		App->fonts->BlitText(26, 450, weaponsFont, "1");
	}
	//App->fonts->BlitText(60, 475, scoreFont, livesText);
	
	//credit
	App->fonts->BlitText(315, 475, scoreFont, "CREDIT ");
	App->fonts->BlitText(370, 475, scoreFont, creditsText);

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	
	if (c1 == collider && dead == false)
	{

		switch (c2->type) {
		case (Collider::Type::WALL):
			if (collider->Intersects(c2->rect)) {
				if (position.x >= c2->rect.x) {

					if (position.y > c2->rect.y + c2->rect.h - 2) {
						position.y += speed;
						if (position.y <= App->render->cameralimits.y + 1) {
							App->render->camera.y -= App->render->cameraSpeed;
						}
					}
					else if (position.y < c2->rect.y - c1->rect.h + 2) {
						position.y -= speed;
						if (position.y + 64 >= App->render->cameralimits.y + App->render->cameralimits.h - 1) {
							App->render->camera.y += App->render->cameraSpeed;
						}
					}
					else {
						position.x += speed;
						if (position.x <= App->render->cameralimits.x + 1) {
							App->render->camera.x -= App->render->cameraSpeed;
						}
					}

				}

				if (position.x < c2->rect.x) {

					if (position.y > c2->rect.y + c2->rect.h - 2) {
						position.y += speed;
						if (position.y <= App->render->cameralimits.y + 1) {
							App->render->camera.y -= App->render->cameraSpeed;
						}
					}
					else if (position.y < c2->rect.y - c1->rect.h + 2) {
						position.y -= speed;
						if (position.y + 64 >= App->render->cameralimits.y + App->render->cameralimits.h - 1) {
							App->render->camera.y += App->render->cameraSpeed;
						}

					}
					else {
						position.x -= speed;
						if (App->player->position.x + 32 >= App->render->cameralimits.x + App->render->cameralimits.w - 1) {
							App->render->camera.x += App->render->cameraSpeed;
						}
					}
				}
			}
			break;
		case (Collider::Type::DESTROYABLE_WALL):
			if (c1->Intersects(c2->rect)) {
				if (position.x >= c2->rect.x) {

					if (position.y > c2->rect.y + c2->rect.h - 2) {
						position.y += speed;
						if (position.y <= App->render->cameralimits.y + 1) {
							App->render->camera.y -= App->render->cameraSpeed;
						}
					}
					else if (position.y < c2->rect.y - c1->rect.h + 2) {
						position.y -= speed;
						if (position.y + 64 >= App->render->cameralimits.y + App->render->cameralimits.h - 1) {
							App->render->camera.y += App->render->cameraSpeed;
						}
					}
					else {
						position.x += speed;
						if (position.x <= App->render->cameralimits.x + 1) {
							App->render->camera.x -= App->render->cameraSpeed;
						}
					}

				}

				if (position.x < c2->rect.x) {

					if (position.y > c2->rect.y + c2->rect.h - 2) {
						position.y += speed;
						if (position.y <= App->render->cameralimits.y + 1) {
							App->render->camera.y -= App->render->cameraSpeed;
						}
					}
					else if (position.y < c2->rect.y - c1->rect.h + 2) {
						position.y -= speed;
						if (position.y + 64 >= App->render->cameralimits.y + App->render->cameralimits.h - 1) {
							App->render->camera.y += App->render->cameraSpeed;
						}

					}
					else {
						position.x -= speed;
						if (App->player->position.x + 32 >= App->render->cameralimits.x + App->render->cameralimits.w - 1) {
							App->render->camera.x += App->render->cameraSpeed;
						}
					}
				}
			}
			break;
		case(Collider::Type::ENEMY_SHOT):
			if (collider->Intersects(c2->rect)) {
				if (collider->Intersects(c2->rect)) {
					lives--;
					//App->fonts->BlitText(60 + 8 * (lives), 450, scoreFont, " ");
					if (lives == 0) {
						dead == true;
						score = 0;
					}
				}
			}
			break;
		case (Collider::Type::POWERUP):
			if (collider->Intersects(c2->rect)) {
				heavyweapon = true;
				normalweapon = false;
			}
		case(Collider::Type::ENEMY):
			if (collider->Intersects(c2->rect)) {
				lives--;
				//App->fonts->BlitText(60 + 8 * (lives), 450, scoreFont, " ");
				if (lives == 0) {
					dead = true;
					score = 0;
				}
			}
			break;
		case(Collider::Type::WATER):
			if (collider->Intersects(c2->rect)==true) {
				waterP = true;
				if (collider->Intersects(c2->rect)==false) {
					waterP = false;
				}
				break;
			}
		/*case(Collider::Type::NONE):
			if (collider->Intersects(c2->rect) == false) {
				waterP = false;
				

			}*/
		case(Collider::Type::PRISONER):
			if (collider->Intersects(c2->rect) == true) {
				granades = 50;
			}
		
		}

		/*if (c2->type == Collider::Type::WATER) {
			if (collider->Intersects(c2->rect) == true) {
				waterP = true;
				if (collider->Intersects(c2->rect) == false) {
					waterP = false;
				}

			}
		}*/

	}

	
}
