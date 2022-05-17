#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender() : Module()
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
update_status ModuleRender::PreUpdate()
{
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Clear rendering target
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	//up

	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {

		if (App->player->position.y <= cameralimits.y) {
			camera.y += cameraSpeed;
			cameralimits.y = App->player->position.y;
		}
	}

	//down

	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
		if (App->player->position.y + 30 >= cameralimits.y + 50) {
			camera.y -= cameraSpeed;
			cameralimits.y = App->player->position.y + 30 - 50;
		}
	}


	// right

	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {

		if (App->player->position.x + 25 >= cameralimits.x + 50) {
			camera.x -= cameraSpeed;
			cameralimits.x = App->player->position.x + 25 - 50;
		}
	}

	//left

	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {

		if (App->player->position.x <= cameralimits.x) {
			camera.x += cameraSpeed;
			cameralimits.x = App->player->position.x;
		}
	}

	//cameral limits

	if (camera.y <= 910) {
		if (camera.x >= 48) {
			camera.x = 48;
		}
		if (camera.x <= -64) {
			camera.x = -64;
		}
		if (camera.y <= -30) {
			camera.y = -30;
		}

	}

	if (camera.y <= 1710 && camera.y > 910) {
		if (camera.y > 1705 && camera.x <= 48 && camera.x >= 10) {
			camera.y = 1705;
		}
		if (camera.x >= 48) {
			camera.x = 48;
		}
		if (camera.x <= -326) {
			camera.x = -326;
		}
	}

	if (camera.y <= 1900 && camera.y > 1710) {
		if (camera.x >= -16) {
			camera.x = -16;
		}
		if (camera.x <= -326) {
			camera.x = -326;
		}
	}

	if (camera.y <= 2250 && camera.y > 1900) {
		if (camera.x >= -16) {
			camera.x = -16;
		}
		if (camera.x <= -616) {
			camera.x = -616;
		}
	}

	if (camera.y <= 2380 && camera.y > 2250) {
		if (camera.x >= -232) {
			camera.x = -232;
		}
		if (camera.x <= -616) {
			camera.x = -616;
		}
	}

	if (camera.y <= 4440 && camera.y > 2380) {
		if (camera.x >= -504) {
			camera.x = -504;
		}
		if (camera.x <= -616) {
			camera.x = -616;
		}
	}

	if (camera.y <= 4640 && camera.y > 4440) {
		if (camera.x >= -504) {
			camera.x = -504;
		}
		if (camera.x <= -986) {
			camera.x = -986;
		}
	}

	if (camera.y <= 5270 && camera.y > 4640) {
		if (camera.x >= -648) {
			camera.x = -648;
		}
		if (camera.x <= -986) {
			camera.x = -986;
		}
	}

	if (camera.y <= 5560 && camera.y > 5270) {
		if (camera.x >= -648) {
			camera.x = -648;
		}
		if (camera.x <= -1112) {
			camera.x = -1112;
		}
	}

	if (camera.y <= 8080 && camera.y > 5560) {
		if (camera.x >= -1048) {
			camera.x = -1048;
		}
		if (camera.x <= -1112) {
			camera.x = -1112;
		}
	}

	//free movement with jikl

	if (App->input->keys[SDL_SCANCODE_L] == KEY_REPEAT)
		camera.x -= cameraSpeed;

	if (App->input->keys[SDL_SCANCODE_J] == KEY_REPEAT)
		camera.x += cameraSpeed;

	if (App->input->keys[SDL_SCANCODE_K] == KEY_REPEAT)
		camera.y -= cameraSpeed;

	if (App->input->keys[SDL_SCANCODE_I] == KEY_REPEAT)
		camera.y += cameraSpeed;


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//Update the screen
	SDL_RenderPresent(renderer);

	return update_status::UPDATE_CONTINUE;
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
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed)
{
	bool ret = true;

	SDL_Rect rect{
		(int)(camera.x * speed) + x * SCREEN_SIZE,
		(int)(camera.y * speed) + y * SCREEN_SIZE,
		0, 0 };

	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
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
		(int)(camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawLine(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	bool line = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	//SDL_RenderDrawLine(renderer, cx, cy, cx + cy * cos(alpha), cy - cy * sin(alpha));
}