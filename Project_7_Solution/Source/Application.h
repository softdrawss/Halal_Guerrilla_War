#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 19

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleController;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;

class SceneIntro;
class ScenePhoto;
class SceneCutscene;
class SceneText;
class ModuleScene;

class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModulePowerUp;
class ModuleFadeToBlack;
class ModuleFonts;
class SceneWin;
class ModuleRender;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleController* controller = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneIntro* sceneIntro = nullptr;
	ScenePhoto* scenePhoto = nullptr;
	SceneCutscene* sceneCutscene = nullptr;
	SceneText* sceneText = nullptr;
	ModuleScene* scene = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModulePowerUp* powerUps = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;
	SceneWin* sceneWin = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__