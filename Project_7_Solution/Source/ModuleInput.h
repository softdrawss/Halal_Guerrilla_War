#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"


#define MAX_KEYS 256
#define MAX_CONTROLLERS 8

enum Key_State
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};


class ModuleInput : public Module
{
public:
	// Constructor
	ModuleInput(bool startEnabled);

	// Destructor
	~ModuleInput();

	// Called on application start.
	// Initializes the SDL system for input detection
	bool Init() override;

	// Called at the beginning of the application loop
	// Updates all input data received from SDL
	Update_Status PreUpdate() override;

	// Called on application exit.
	// Uninitializes the SDL system for input detection
	bool CleanUp() override;

	
	Key_State keys[MAX_KEYS] = { KEY_IDLE };

};

#endif // __ModuleInput_H__