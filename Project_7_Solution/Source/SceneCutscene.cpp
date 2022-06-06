#include "SceneCutscene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"
#include "SDL/include/SDL_scancode.h"
#include "ModuleFonts.h"
#include <stdio.h>

SceneCutscene::SceneCutscene(bool startEnabled) : Module(startEnabled) {

}

SceneCutscene::~SceneCutscene() {

}

// Load assets
bool SceneCutscene::Start() {
	bool ret = true;

	bgTexture = App->textures->Load("Assets/title_map_large.png");
	introAssets = App->textures->Load("Assets/intro_assets.png");
	titleImage = App->textures->Load("Assets/intro_assets.png");
	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.@'?&- " };
	introFont = App->fonts->Load("Assets/ui_font5.png", lookupTable, 1);

	App->audio->PlayMusic("Assets/gwar-112.wav", 1.0f);
	duration = 0;

	bombsAnim.FullReset();
	bombsAnim.PushBack({ 0 , 160, 16, 16 });
	bombsAnim.PushBack({ 16, 160, 16, 16 });
	bombsAnim.PushBack({ 32, 160, 16, 16 });
	bombsAnim.PushBack({ 48, 160, 16, 16 });
	bombsAnim.PushBack({ 64, 160, 16, 16 });
	bombsAnim.PushBack({ 80, 160, 16, 16 });
	bombsAnim.PushBack({ 96, 160, 16, 16 });
	bombsAnim.PushBack({ 0  , 176, 32, 64 });
	bombsAnim.PushBack({ 32 , 176, 32, 64 });
	bombsAnim.PushBack({ 64 , 176, 32, 64 });
	bombsAnim.PushBack({ 96 , 176, 32, 64 });
	bombsAnim.PushBack({ 128, 176, 32, 64 });
	bombsAnim.PushBack({ 160, 176, 32, 64 });
	bombsAnim.PushBack({ 192, 176, 32, 64 });
	bombsAnim.speed = 0.15f;
	bombsAnim.loop = false;

	planesAnim.FullReset();
	planesAnim.PushBack({ 224, 112, 128, 128 });
	planesAnim.loop = false;

	playerMiniAnim.FullReset();
	playerMiniAnim.PushBack({ 0  , 0, 32, 32 });
	playerMiniAnim.PushBack({ 32 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 64 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 96 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 128, 0, 32, 32 });
	playerMiniAnim.PushBack({ 160, 0, 32, 32 });
	playerMiniAnim.PushBack({ 192, 0, 32, 32 });
	playerMiniAnim.PushBack({ 224, 0, 32, 32 });
	playerMiniAnim.PushBack({ 256, 0, 32, 32 });
	playerMiniAnim.PushBack({ 288, 0, 32, 32 });
	playerMiniAnim.PushBack({ 320, 0, 32, 32 });
	playerMiniAnim.PushBack({ 352, 0, 32, 32 });
	playerMiniAnim.loop = false;
	playerMiniAnim.speed = 0.21f;

	boatAnim.FullReset();
	boatAnim.PushBack({ 0 , 64, 32, 96 });
	boatAnim.PushBack({ 32, 64, 32, 96 });
	boatAnim.PushBack({ 64, 64, 32, 96 });
	boatAnim.PushBack({ 96, 64, 32, 96 });
	boatAnim.loop = true;
	boatAnim.speed = 0.1f;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	assetsPoint[0] = &boat;
	assetsPoint[1] = &playerMini;
	assetsPoint[2] = &bombs[0];
	assetsPoint[3] = &bombs[1];
	assetsPoint[4] = &bombs[2];
	assetsPoint[5] = &bombs[3];
	assetsPoint[6] = &bombs[4];
	assetsPoint[7] = &bombs[5];
	assetsPoint[8] = &bombs[6];
	assetsPoint[9] = &bombs[7];
	assetsPoint[10] = &planes[0];
	assetsPoint[11] = &planes[1];
	assetsPoint[12] = &planes[2];


	assetsAnim[0] = boatAnim;
	assetsAnim[1] = playerMiniAnim;
	assetsAnim[2] = bombsAnim;
	assetsAnim[3] = bombsAnim;
	assetsAnim[4] = bombsAnim;
	assetsAnim[5] = bombsAnim;
	assetsAnim[6] = bombsAnim;
	assetsAnim[7] = bombsAnim;
	assetsAnim[8] = bombsAnim;
	assetsAnim[9] = bombsAnim;
	assetsAnim[10] = planesAnim;
	assetsAnim[11] = planesAnim;
	assetsAnim[12] = planesAnim;

	boat.x = (SCREEN_WIDTH / 2) - 8;
	boat.y = (SCREEN_HEIGHT / 2) + 64;

	planes[0].x = (SCREEN_WIDTH / 2) - 55;
	planes[0].y = SCREEN_HEIGHT + 96;
	planes[1].x = 0 - 32;
	planes[1].y = SCREEN_HEIGHT + 128 + 96;
	planes[2].x = SCREEN_WIDTH - 96;
	planes[2].y = SCREEN_HEIGHT + 128 + 96;

	playerMini.x = -32;
	bombs[0].x = SCREEN_WIDTH;
	bombs[1].x = -32;
	bombs[2].x = SCREEN_WIDTH;
	bombs[3].x = -32;
	bombs[4].x = SCREEN_WIDTH;
	bombs[5].x = -32;
	bombs[6].x = SCREEN_WIDTH;
	bombs[7].x = -32;

	titleAnim.FullReset();
	titleAnim.PushBack({ 0, 240, 207, 158 });
	titleAnim.loop = false;
	title.x = 110;
	title.y = 125;
	return ret;
}

Update_Status SceneCutscene::Update() {

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || duration >= SCENE_DURATION) {
		App->fade->FadeToBlack(this, (Module*)App->sceneText, 100);
	}
	/*int planeAudio = App->audio->LoadFx("Assets/gwar-130.wav");
	App->audio->PlayFx(planeAudio, 0);*/

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN) {
		return Update_Status::UPDATE_STOP;
	}

	if (duration < 360) {
		App->render->camera.y -= 2 * SCREEN_SIZE;
	}
	if (duration < 400 && duration >= 360) {
		App->render->camera.y -= 1 * SCREEN_SIZE;
	}
	if (duration < 360) {
		boat.y -= 4;
	}
	if (duration < 405 && duration >= 360) {
		boat.y -= 2;
	}

	if (duration == 180) {
		assetsAnim[2].Reset();
		bombs[0].x = (SCREEN_WIDTH / 2) - 8;
		bombs[0].y = -328; //-176
	}
	if (duration == 185) {
		assetsAnim[3].Reset();
		bombs[1].x = (SCREEN_WIDTH / 2) - 8;
		bombs[1].y = -388; //-206
	}
	if (duration == 200) {
		assetsAnim[4].Reset();
		bombs[2].x = (SCREEN_WIDTH / 2) - 8;
		bombs[2].y = -448; //-236
	}
	if (duration == 210) {
		assetsAnim[5].Reset();
		bombs[3].x = (SCREEN_WIDTH / 2) - 8;
		bombs[3].y = -508; //-266
	}
	if (duration == 220) {
		assetsAnim[6].Reset();
		bombs[4].x = (SCREEN_WIDTH / 2) - 8;
		bombs[4].y = -568; //-296
	}
	if (duration == 230) {
		assetsAnim[7].Reset();
		bombs[5].x = (SCREEN_WIDTH / 2) - 8;
		bombs[5].y = -628; //-326
	}
	if (duration == 240) {
		assetsAnim[8].Reset();
		bombs[6].x = (SCREEN_WIDTH / 2) - 8;
		bombs[6].y = -688; //-356
	}
	if (duration == 250) {
		assetsAnim[9].Reset();
		bombs[7].x = (SCREEN_WIDTH / 2) - 8;
		bombs[7].y = -748; //-386
	}
	if (duration == 475) {
		assetsAnim[1].Reset();
		playerMini.x = boat.x;
		playerMini.y = boat.y + 16;
		int miniPlayerSound = App->audio->LoadFx("Assets/gwar-184.wav");
		App->audio->PlayFx(miniPlayerSound, 0);
	}
	
	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) {
			if (assetsAnim[i + 2].GetCurrentFrameint() < 6) {
				bombs[i].x += 1;
				bombs[i].y -= 4;
			}
		}
		else {
			if (assetsAnim[i + 2].GetCurrentFrameint() < 6) {
				bombs[i].x -= 1;
				bombs[i].y -= 4;
			}
		}
	}

	if (assetsAnim[1].GetCurrentFrameint() < 8) {
		playerMini.x -= 1;
		playerMini.y -= 1;
	}

	planes[0].y -= 6;
	planes[1].y -= 6;
	planes[2].y -= 6;

	for (int i = 0; i < MAX_ASSETS_TITLE; ++i) {
		assetsAnim[i].Update();
	}
	++duration;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneCutscene::PostUpdate() {
	App->render->Blit(bgTexture, 5, SCREEN_HEIGHT - 2120, NULL);

	for (int i = 0; i < MAX_ASSETS_TITLE; ++i) {
		SDL_Rect rect = assetsAnim[i].GetCurrentFrame();
		App->render->Blit(introAssets, assetsPoint[i]->x, assetsPoint[i]->y, &rect);
	}

	sprintf_s(App->sceneIntro->creditsText, 10, "%d", App->sceneIntro->credits);

	SDL_Rect titleREC = titleAnim.GetCurrentFrame();

	// Highscore of the level (if you kill all the enemies and save the prisoners)
	App->fonts->BlitText(130, 75, introFont, "HI");
	App->fonts->BlitText(250, 75, introFont, "30000");

	// Player 1 --> Available
	App->fonts->BlitText(83, 85, introFont, "1 UP");
	App->fonts->BlitText(125, 95, introFont, "0");

	// Player 2 --> Not available
	App->fonts->BlitText(290, 85, introFont, "2 UP");
	App->fonts->BlitText(330, 95, introFont, "0");

	App->render->Blit(titleImage, title.x, title.y, &titleREC, NULL, false);
	App->fonts->BlitText(315, 475, introFont, "CREDIT ");
	App->fonts->BlitText(370, 475, introFont, App->sceneIntro->creditsText);
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneCutscene::CleanUp() {
	App->textures->Unload(bgTexture);
	App->textures->Unload(introAssets);
	App->textures->Unload(titleImage);
	App->fonts->UnLoad(introFont);
	bgTexture = nullptr;
	introAssets = nullptr;
	titleImage = nullptr;
	return true;
}