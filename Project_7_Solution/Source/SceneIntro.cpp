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

	bgTexture = App->textures->Load("Assets/names.png");
	App->audio->PlayMusic("Assets/gwar-110.wav", 1.0f);
	//App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.@'?&- " };
	introFont = App->fonts->Load("Assets/ui_font5.png", lookupTable, 1);
	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		credits++;
		int audioCredit = App->audio->LoadFx("Assets/gwar-191.wav");
		App->audio->PlayFx(audioCredit);
	}

	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN && credits>0) {
		App->fade->FadeToBlack(this, (Module*)App->scenePhoto, 20);
		
		
		credits--;
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	sprintf_s(creditsText, 10, "%d", credits);

	App->render->Blit(bgTexture, 0, 30, NULL);
	App->fonts->BlitText(315, 475, introFont, "CREDIT ");
	App->fonts->BlitText(370, 475, introFont, creditsText);
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp() 
{
	App->textures->Unload(bgTexture);
	App->fonts->UnLoad(introFont);
	bgTexture = nullptr;
	return true;
}