#include "SceneText.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include <stdio.h>

SceneText::SceneText(bool startEnabled) : Module(startEnabled)
{

}

SceneText::~SceneText()
{

}

// Load assets
bool SceneText::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/text_intro.png");
	App->audio->PlayMusic("Assets/gwar-110.wav", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.@'?&- " };
	introFont = App->fonts->Load("Assets/ui_font5.png", lookupTable, 1);
	return ret;
}

Update_Status SceneText::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene, 20);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneText::PostUpdate()
{
	// Draw everything --------------------------------------
	sprintf_s(App->sceneIntro->creditsText, 10, "%d", App->sceneIntro->credits);

	App->render->Blit(bgTexture, 0, 30, NULL);
	App->fonts->BlitText(315, 475, introFont, "CREDIT ");
	App->fonts->BlitText(370, 475, introFont, App->sceneIntro->creditsText);
	return Update_Status::UPDATE_CONTINUE;
}

bool SceneText::CleanUp()
{
	App->textures->Unload(bgTexture);
	App->fonts->UnLoad(introFont);
	bgTexture = nullptr;
	return true;
}