#include "SceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include <stdio.h>

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled)
{

}

SceneWin::~SceneWin()
{

}

// Load assets
bool SceneWin::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/win.png");
	App->audio->PlayMusic("Assets/gwar-127.wav");
	
	//App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

Update_Status SceneWin::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 100);

	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneWin::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(bgTexture, 100, 100, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneWin::CleanUp()
{
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	return true;
}