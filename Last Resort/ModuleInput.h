#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 150
#define DEATHZONE  6400
#define MAX_GAME_CONTROLLERS 2

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	SDL_Event _e;



	//GAMEPADS

	SDL_Event gamepadevent;         //Event to control gamepads status

	// GAMEPAD ---PLAYER1---

	SDL_GameController*Player1_Gamepad = nullptr;

	bool Player1_Gamepad_Connected = false;             //boolean that checks if the gamepad is connected.
	bool Player1_Gamepad_A_pressed = false;             //boolean that checks if the A button is pressed.
	bool Player1_Gamepad_RightShoulder_pressed = false; //boolean that checks if the RightShoulder button is pressed. 
	bool Player1_Gamepad_Start_pressed = false;         //boolean that checks if the Start button is pressed.

	//Values assigned to the Joysticks Axes

	int Player1_Gamepad_LAxisX = 0;
	int Player1_Gamepad_LAxisY = 0;


	// GAMEPAD ---PLAYER2---

	SDL_GameController*Player2_Gamepad = nullptr;

	bool Player2_Gamepad_Connected = false;             //boolean that checks if the gamepad is connected.
	bool Player2_Gamepad_A_pressed = false;             //boolean that checks if the A button is pressed.
	bool Player2_Gamepad_RightShoulder_pressed = false; //boolean that checks if the RightShoulder button is pressed. 
	bool Player2_Gamepad_Start_pressed = false;         //boolean that checks if the Start button is pressed.

	//Values assigned to the Joysticks Axes

	int Player2_Gamepad_LAxisX = 0;
	int Player2_Gamepad_LAxisY = 0;
};

#endif // __ModuleInput_H__