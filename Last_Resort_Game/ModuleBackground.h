#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;


class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* backbackground = nullptr;
	SDL_Texture* midbackground = nullptr;
	SDL_Texture* road = nullptr;
	SDL_Texture* bossimg = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect midback;
	SDL_Rect bossplace;
	Mix_Music* maintracklvl1 = nullptr;
};

#endif