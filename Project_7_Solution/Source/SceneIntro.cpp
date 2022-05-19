#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

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

	return ret;
}

Update_Status SceneIntro::Update()
{


	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) {
		bgTexture = App->textures->Load("Assets/title.png");
		App->fade->FadeToBlack(this, (Module*)App->scene, 150);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, -50, 50, NULL);

	return Update_Status::UPDATE_CONTINUE;
}