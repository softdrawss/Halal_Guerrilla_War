#include "ModuleScene.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePowerUp.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
	background.x = 0;
	background.y = 0;
	background.w = 1117;
	background.h = 4576;
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Guerrilla_War_ARC_Map_Level1 copia.png");
	App->audio->PlayMusic("Assets/gwar-107.ogg", 1.0f);
	
	//left wall colliders
	App->collisions->AddCollider({ -30, 420, 64,105 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30,381, 93,39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, 345, 124,36 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, 240, 160,105 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, 200, 200,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, 25, 230,175 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -35, 200,60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -65, 170,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -95, 140,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -265, 125,170 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -330, 165,65 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -365, 195,35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -535, 230,170 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -595, 200,60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -625, 170,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -655, 140,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -825, 125,170 }, Collider::Type::WALL);
	App->collisions->AddCollider({ -30, -870, 165,45 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 135, -890, 280,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 135, -920, 310,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 135, -1100, 345,180 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 135, -1200, 320,100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 135, -1315, 290,115 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 135, -1465, 310,150 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 250, -1660, 10,195 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 355, -1585, 70,35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 250, -1690, 175,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 250, -2185, 70,350 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, -1920, 20,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, -2060, 20,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, -2130, 20,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 250, -2290, 105,35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 250, -2360, 175,70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 250, -2440, 135,80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 250, -2480, 175,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 320, -2580, 210,100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 320, -2790, 350,210 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 320, -2830, 310,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 320, -2870, 270,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 500, -3425, 90,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 500, -3635, 135,210 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 500, -3845, 165,210 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 500, -4045, 600,200 }, Collider::Type::WALL);

	//right wall colliders
	App->collisions->AddCollider({ 470, 480, 64,45 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 440, 420, 94,60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 400, 380, 135,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, 310, 175,70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 335, 275, 200,35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, -45, 235,320 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 335, -255, 200,210 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, -615, 235,360 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, -645, 170,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 450, -695, 140,50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 550, -865, 80,170 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 590, -1165, 120,300 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 615, -1240, 120,75 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 590, -1470, 200,230 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 790, -1660, 40,195 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 605, -1585, 70,35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 605, -1690, 210,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 660, -2185, 190,350 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 550, -1920, 20,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 550, -2060, 20,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 550, -2130, 20,30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 710, -2290, 210,35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 700, -2380, 280,90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 770, -2420, 200,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 880, -2460, 60,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 900, -2790, 60,330 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 930, -2830, 100,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 970, -2870, 100,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 960, -3425, 90,40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 930, -3735, 135,310 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 920, -3595, 40,35 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 960, -3845, 135,110 }, Collider::Type::WALL);

	//destroyable wall, warsacks, tanktraps and etc
	//App->collisions->AddCollider({ 110, -205, 36,25 }, Collider::Type::DESTROYABLE_WALL);
	//App->collisions->AddCollider({ 146, -205, 36,25 }, Collider::Type::DESTROYABLE_WALL);
	//App->collisions->AddCollider({ 250, -205, 36,25 }, Collider::Type::DESTROYABLE_WALL);
	//App->collisions->AddCollider({ 286, -205, 36,25 }, Collider::Type::DESTROYABLE_WALL);

	//prisoners
	

	// Water
	App->collisions->AddCollider({ 200, 305, 100,900 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 60, 475, 40,500 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 100, 450, 50,500 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 150, 400, 25, 150 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 175, 375, 25,500 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 300, 375, 30, 500 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 300, 340, 30, 35 }, Collider::Type::WATER);

	App->collisions->AddCollider({ 330, 400, 20, 150 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 350, 450, 60, 150 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 500, -3354, 280, 442 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 850, -3354, 275, 442 }, Collider::Type::WATER);

	//// Enemies
	//App->enemies->AddEnemy(Enemy_Type::BOMB, 398, -2290, 0);
	//App->enemies->AddEnemy(Enemy_Type::BOMB, 500, -2290, 0); 
	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, 0, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, 0, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, 0, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -60, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, -60, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, -60, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -100, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, -100, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, -100, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -140, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, -140, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, -140, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 250, -205, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 150, -205, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 200, -225, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -300, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, -300, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, -300, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 260, -300, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -360, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, -360, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, -360, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -410, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, -410, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, -410, 1);

	App->enemies->AddEnemy(Enemy_Type::RED, 240, -410, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -480, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 230, -480, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 300, -600, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 80, -680, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 200, -480, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 220, -480, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 240, -480, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 260, -480, 1);

	App->enemies->AddEnemy(Enemy_Type::RED, 400, -600, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 160, -850, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 190, -850, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 210, -850, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 500, -800, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 470, -1000, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 510, -1000, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 550, -1000, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 470, -1200, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 510, -1210, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 550, -1290, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 470, -1300, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 510, -1320, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 550, -13600, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 470, -1450, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 510, -1480, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 550, -1500, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 470, -1600, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 510, -1630, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 550, -1700, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 440, -1500, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 440, -1550, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 740, -1500, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 740, -1550, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 740, -1600, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 740, -1650, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 740, -1700, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 440, -1600, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 440, -1650, 0);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 440, -1700, 0);

	App->enemies->AddEnemy(Enemy_Type::RED, 440, -1800, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 740, -1800, 0);

	App->enemies->AddEnemy(Enemy_Type::RED, 640, -1800, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 640, -1920, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 640, -1990, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 640, -2050, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 640, -2190, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 640, -2300, 0);

	App->enemies->AddEnemy(Enemy_Type::RED, 340, -1800, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 340, -1920, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 340, -1990, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 340, -2050, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 340, -2190, 0);
	App->enemies->AddEnemy(Enemy_Type::RED, 340, -2300, 0);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 700, -2600, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 740, -2600, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 780, -2600, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 820, -2600, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 700, -2900, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 740, -2900, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 780, -2900, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 820, -2900, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 780, -3100, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 820, -3100, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 780, -3300, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 820, -3300, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 780, -3500, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 820, -3500, 1);

	App->enemies->AddEnemy(Enemy_Type::GREEN, 780, -3700, 1);
	App->enemies->AddEnemy(Enemy_Type::GREEN, 820, -3700, 1);

	App->enemies->AddEnemy(Enemy_Type::BOSS, 800, -4000, 0);

















	//App->enemies->AddEnemy(Enemy_Type::GREEN, 240, 0,1);

	//App->enemies->AddEnemy(Enemy_Type::GREEN, 180, 200, 0);


	//prisoners
	//App->powerUps->AddPowerUp(PowerUp_Type::PRISONER, 220, 0);
	
	//App->enemies->AddEnemy(Enemy_Type::BOSS, 220, 0, 0);


	//Enable the necessary modules
	App->collisions->Enable();
	App->particles->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->powerUps->Enable();
	return ret;
}

Update_Status ModuleScene::Update()
{
	if (App->player->position.y <= 290) {
		//App->audio->PlayMusic("Assets/gwar-107.wav", 1.0f);
		//Mix_Pause(-1);
		//App->audio->CleanUp();
		//App->audio->Init();
		//App->audio->PlayMusic("Assets/gwar-104.wav", 1.0f);
		//uint boss = App->audio->LoadFx("Assets/gwar-104.wav");
		//App->audio->PlayFx(boss, -1);
		//App->audio->PlayFx(boss, -1);
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, -30, -4050, &background, 1);

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	//App->audio->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->particles->Disable();
	App->powerUps->Disable();
	return true;
}

