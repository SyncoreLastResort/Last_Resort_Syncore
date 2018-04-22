#ifndef __MODULEGAMEOVER_H__
#define __MODULEGAMEOVER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleGameOver : public Module
{
public:

	ModuleGameOver();
	~ModuleGameOver();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect background;
	SDL_Texture *graphics;
	Mix_Music *gameover_Sound = nullptr;
};


#endif
