#ifndef __MODULE_SCENETITLE_H__
#define __MODULE_SCENETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#define MAX_ASSETS_TITLE 13

struct SDL_Texture;

class SceneCutscene : public Module {
public:
	// Constructor
	SceneCutscene(bool startEnabled);

	// Destructor
	~SceneCutscene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player, the enemies and the powerups.
	bool CleanUp();


public:
	// Scene duration
	uint duration;

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* introAssets = nullptr;
	SDL_Texture* titleImage = nullptr;

	// Textures & Animations
	iPoint planes[3];
	Animation planesAnim;

	iPoint boat;
	Animation boatAnim;

	iPoint bombs[8];
	Animation bombsAnim;

	iPoint playerMini;
	Animation playerMiniAnim;

	iPoint title;
	Animation titleAnim;

	iPoint* assetsPoint[MAX_ASSETS_TITLE];
	Animation assetsAnim[MAX_ASSETS_TITLE];

	int introFont = -1;
	char creditsText[10] = { "\0" };
};

#endif // __MODULE_SCENETITLE_H__

