#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"


#include "SDL/include/SDL_render.h"

ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled)
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
Update_Status ModuleRender::PreUpdate()
{
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Clear rendering target
	SDL_RenderClear(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::Update() {

	if (App->player->IsEnabled() == true) {
		//camera movement

	//up

		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {

			if (App->player->position.y <= cameralimits.y) {
				camera.y -= cameraSpeed;
				cameralimits.y = App->player->position.y;
			}
		}

		//down

		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			if (App->player->position.y + 30 >= cameralimits.y + 50) {
				camera.y += cameraSpeed;
				cameralimits.y = App->player->position.y + 30 - 50;
			}
		}


		// right

		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {

			if (App->player->position.x + 25 >= cameralimits.x + 50) {
				camera.x += cameraSpeed;
				cameralimits.x = App->player->position.x + 25 - 50;
			}
		}

		//left

		if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {

			if (App->player->position.x <= cameralimits.x) {
				camera.x -= cameraSpeed;
				cameralimits.x = App->player->position.x;
			}
		}
	}
	//camera limits

	if (App->scene->IsEnabled() == true) {
		if (camera.y >= -882) {
			if (camera.x >= 110) {
				camera.x = 110;
			}
			if (camera.x <= -28) {
				camera.x = -28;
			}
			if (camera.y >= 570 - camera.h) {
				camera.y = 570 - camera.h;
			}
		}
		else if (camera.y >= -1090 && camera.y < -882) {
			if (camera.x >= 110) {
				camera.x = 110;
			}
			if (camera.x <= 15) {
				camera.x = 15;
			}
		}
		else if (camera.y >= -1154 && camera.y < -1090) {
			if (camera.x >= 230) {
				camera.x = 230;
			}
			if (camera.x <= 5) {
				camera.x = 5;
			}
		}
		else if (camera.y >= -1230 && camera.y < -1154) {
			if (camera.x >= 230) {
				camera.x = 230;
			}

			if (camera.x <= 130) {
				camera.x = 130;
			}
		}
		else if (camera.y >= -1582 && camera.y < -1230) {
			if (camera.x >= 230) {
				camera.x = 230;
			}

			if (camera.x <= 260) {
				camera.x = 260;
			}
		}
		else if (camera.y >= -2354 && camera.y < -1582) {
			if (camera.x >= 410) {
				camera.x = 410;
			}

			if (camera.x <= 260) {
				camera.x = 260;
			}
		}
		else if (camera.y >= -2814 && camera.y < -2354) {
			if (camera.x >= 410) {
				camera.x = 410;
			}
			if (camera.x <= 330) {
				camera.x = 330;
			}
		}
		else if (camera.y >= -2846 && camera.y < -2814) {
			if (camera.x >= 410) {
				camera.x = 410;
			}
			if (camera.x <= 530) {
				camera.x = 530;
			}
		}
		else if (camera.y >= -3270 && camera.y < -2846) {
			if (camera.x >= 570) {
				camera.x = 570;
			}
			if (camera.x <= 530) {
				camera.x = 530;
			}
		}
		else if (camera.y >= -4082 && camera.y < -3270) {
			if (camera.x >= 630) {
				camera.x = 630;
			}
			if (camera.x <= 530) {
				camera.x = 530;
			}
		}
		if (camera.y <= -4082) {
			camera.y = -4082;
		}
	}
	
	//free movement with jikl

	if (App->input->keys[SDL_SCANCODE_L] == KEY_REPEAT) {
		camera.x += cameraSpeed;
	}
	if (App->input->keys[SDL_SCANCODE_J] == KEY_REPEAT) {
		camera.x -= cameraSpeed;
	}
	if (App->input->keys[SDL_SCANCODE_K] == KEY_REPEAT) {
		camera.y += cameraSpeed;
	}
	if (App->input->keys[SDL_SCANCODE_I] == KEY_REPEAT) {
		camera.y -= cameraSpeed;
	}

	return Update_Status::UPDATE_CONTINUE;
}


Update_Status ModuleRender::PostUpdate()
{
	//Update the screen
	SDL_RenderPresent(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, bool useCamera)
{
	bool ret = true;

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + x * SCREEN_SIZE,
		(int)(-camera.y * speed) + y * SCREEN_SIZE,
		0, 0 };

	if (useCamera)
	{
		dstRect.x -= (camera.x * speed);
		dstRect.y -= (camera.y * speed);
	}

	if (section != nullptr)
	{
		dstRect.w = section->w;
		dstRect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
	}

	dstRect.w *= SCREEN_SIZE;
	dstRect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &dstRect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	dstRect.x -= (camera.x * speed);
	dstRect.y -= (camera.y * speed);
	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
