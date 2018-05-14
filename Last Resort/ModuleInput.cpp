#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;

}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	LOG("Init gamepads system");

	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);


	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) 
	{
		LOG("Gamepad system could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	while (SDL_PollEvent(&_e))	// If user presses X, quit app
	{
		if (_e.type == SDL_QUIT)
		{
			return update_status::UPDATE_STOP;
		}
	}



	//GAMEPAD INPUT SYSTEM


	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{

		if (SDL_IsGameController(i)) 
		{
			if (i == 0) 
			{

				Player1_Gamepad = SDL_GameControllerOpen(i);

				//Checking if PLAYER1's gamepad is attached

				if (SDL_GameControllerGetAttached(Player1_Gamepad)) 
				{

					//Assigning the values of the axis to the integers Controller_Player1_LAxisX...

					Player1_Gamepad_LAxisX = SDL_GameControllerGetAxis(Player1_Gamepad, SDL_CONTROLLER_AXIS_LEFTX);
					Player1_Gamepad_LAxisY = SDL_GameControllerGetAxis(Player1_Gamepad, SDL_CONTROLLER_AXIS_LEFTY);

					//Assigning the boolean values to the booleans defined in input.h  

					Player1_Gamepad_A_pressed = SDL_GameControllerGetButton(Player1_Gamepad, SDL_CONTROLLER_BUTTON_A);
					/*Player1_Gamepad_RightShoulder_pressed = SDL_GameControllerGetButton(Player1_Gamepad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);*/
					Player1_Gamepad_Start_pressed = SDL_GameControllerGetButton(Player1_Gamepad, SDL_CONTROLLER_BUTTON_START);

					Player1_Gamepad_Connected = true;
				}

				else 
				{

					SDL_GameControllerClose(Player1_Gamepad);
					Player1_Gamepad = nullptr;
					Player1_Gamepad_Connected = false;

				}

			}

			else if (i < 1) 
			{

				Player2_Gamepad_Connected = false;
				SDL_GameControllerClose(Player2_Gamepad);
				Player2_Gamepad = nullptr;

			}

			else if (i == 1 || i == 0 && Player1_Gamepad_Connected == false) 
			{

				Player2_Gamepad = SDL_GameControllerOpen(i);

				//Checking if PLAYER2's gamepad is attached

				if (SDL_GameControllerGetAttached(Player2_Gamepad)) 
				{

					Player2_Gamepad_LAxisX = SDL_GameControllerGetAxis(Player2_Gamepad, SDL_CONTROLLER_AXIS_LEFTX);
					Player2_Gamepad_LAxisY = SDL_GameControllerGetAxis(Player2_Gamepad, SDL_CONTROLLER_AXIS_LEFTY);

					//Assigning the boolean values to the booleans defined in input.h 

					Player2_Gamepad_A_pressed = SDL_GameControllerGetButton(Player2_Gamepad, SDL_CONTROLLER_BUTTON_A);
					/*	Player2_Gamepad_RightShoulder_pressed = SDL_GameControllerGetButton(Player2_Gamepad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);*/
					Player2_Gamepad_Start_pressed = SDL_GameControllerGetButton(Player2_Gamepad, SDL_CONTROLLER_BUTTON_START);

					Player2_Gamepad_Connected = true;
					break;


				}

				else 

				{

					SDL_GameControllerClose(Player2_Gamepad);
					Player2_Gamepad = nullptr;
					Player2_Gamepad_Connected = false;

				}
			}
		}
	}

	//Checking PLAYER1's Left Axis X & Y

	if (Player1_Gamepad_LAxisX > 6400) 
	{

		App->input->keyboard[SDL_SCANCODE_D] = KEY_STATE::KEY_REPEAT;

	}
	else if (Player1_Gamepad_LAxisX <-DEATHZONE) 
	{

		App->input->keyboard[SDL_SCANCODE_A] = KEY_STATE::KEY_REPEAT;

	}

	if (Player1_Gamepad_LAxisY < -DEATHZONE) 
	{

		App->input->keyboard[SDL_SCANCODE_W] = KEY_STATE::KEY_REPEAT;

	}
	else if (Player1_Gamepad_LAxisY > DEATHZONE) 
	{

		App->input->keyboard[SDL_SCANCODE_S] = KEY_STATE::KEY_REPEAT;

	}


	//Checking PLAYER1's gamepad buttons

	if (Player1_Gamepad_A_pressed == true && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_IDLE) 
	{

		App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_DOWN;

	}

	else if (Player1_Gamepad_A_pressed == true) 
	{

		App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_REPEAT;

	}

	/*if (Player1_Gamepad_RightShoulder_pressed == true && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_IDLE)
	{

		App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_DOWN;

	}

	else if (Player1_Gamepad_RightShoulder_pressed == true)
	{

		App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_REPEAT;

	}*/



	//Checking PLAYER2's Left Axis X & Y

	if (Player2_Gamepad_LAxisX > DEATHZONE) 
	{

		App->input->keyboard[SDL_SCANCODE_RIGHT] = KEY_STATE::KEY_REPEAT;

	}
	else if (Player2_Gamepad_LAxisX <-DEATHZONE) 
	{

		App->input->keyboard[SDL_SCANCODE_LEFT] = KEY_STATE::KEY_REPEAT;

	}

	if (Player2_Gamepad_LAxisY < -DEATHZONE)
	{

		App->input->keyboard[SDL_SCANCODE_UP] = KEY_STATE::KEY_REPEAT;

	}
	else if (Player2_Gamepad_LAxisY > DEATHZONE) 
	{

		App->input->keyboard[SDL_SCANCODE_DOWN] = KEY_STATE::KEY_REPEAT;

	}


	//Checking PLAYER2's gamepad buttons

	if (Player2_Gamepad_A_pressed == true && App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_IDLE) 
	{

		App->input->keyboard[SDL_SCANCODE_RCTRL] = KEY_STATE::KEY_DOWN;

	}

	else if (Player2_Gamepad_A_pressed == true) 
	{

		App->input->keyboard[SDL_SCANCODE_RCTRL] = KEY_STATE::KEY_REPEAT;

	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	SDL_GameControllerClose(Player1_Gamepad);
	SDL_GameControllerClose(Player2_Gamepad);

	Player1_Gamepad = nullptr;
	Player2_Gamepad = nullptr;

	return true;
}
