#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include <stdio.h>

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Intro.png");

	//App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.@'?&- " };
	App->player->scoreFont = App->fonts->Load("Assets/ui_font5.png", lookupTable, 1);
	return ret;
}

Update_Status SceneIntro::Update()
{


	

	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN) {
		App->player->credits++;
		
		
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && App->player->credits>0) {

		bgTexture = App->textures->Load("Assets/title.png");

		App->fade->FadeToBlack(this, (Module*)App->scene, 200);
		App->player->credits--;
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	sprintf_s(App->player->creditsText, 10, "%d", App->player->credits);

	App->render->Blit(bgTexture, -50, 50, NULL);
	App->fonts->BlitText(315, 475, App->player->scoreFont, "CREDIT ");
	App->fonts->BlitText(370, 475, App->player->scoreFont, App->player->creditsText);
	return Update_Status::UPDATE_CONTINUE;
}