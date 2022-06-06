#ifndef __MODULE_CONTROLLER_H__
#define __MODULE_CONTROLLER_H__

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"
#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

#define MAX_BUTTONS 150
#define DEATHZONE  15000
#define MAX_GAME_CONTROLLERS 2

class ModuleController : public Module
{
public:
    ModuleController(bool startEnabled);
    ~ModuleController();


    bool Init();
    Update_Status PreUpdate();
    bool CleanUp();

public:

    SDL_Event event;

    //GAME CONTROLLER 1

    SDL_GameController* Controller_player1 = nullptr;

    bool Controller_player1_Connected = false;                //controller connected?
    bool controller_player1_A_pressed = false;                //button A pressed?
    bool controller_player1_RightShoulder_pressed = false;    //button RightShoulder pressed?
    bool controller_player1_Start_pressed = false;            //button Start pressed?
    bool controller_player1_B_pressed = false;                //button B pressed?
    bool controller_player1_X_pressed = false;                //button X pressed?

    //values for the Joysticks Axes
    int Controller_player1_LAxisX = 0;
    int Controller_player1_LAxisY = 0;
    int Controller_player1_RAxisX = 0;
    int Controller_player1_RAxisY = 0;
    //=========================================

    //GAME CONTROLLER 2

    SDL_GameController* Controller_player2 = nullptr;

    bool Controller_player2_Connected = false;                //controller connected?
    bool controller_player2_A_pressed = false;                //button A pressed?
    bool controller_player2_RightShoulder_pressed = false;    //button RightShoulder pressed?
    bool controller_player2_Start_pressed = false;            //button Start pressed?
    bool controller_player2_B_pressed = false;                //button B pressed?


    //values for the Joysticks Axes
    int Controller_player2_LAxisX = 0;
    int Controller_player2_LAxisY = 0;

};
#endif // __ModuleInput_H__