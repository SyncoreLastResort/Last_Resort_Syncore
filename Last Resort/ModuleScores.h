#ifndef __MODULESCORES_H__
#define __MODULESCORES_H__

#include "Module.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;


class ModuleScores : public Module
{
public:
	ModuleScores();
	~ModuleScores();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* backgroundscores = nullptr;
	SDL_Texture* scoresranking = nullptr;
	SDL_Rect backgroundrect;
	SDL_Rect scoresrect;
	Mix_Music *scores_Sound = nullptr;
};

#endif