#ifndef __MODULESCORES_H__
#define __MODULESCORES_H__

#include "Module.h"

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
	SDL_Rect backgroundrect;
	Mix_Music *scores_Sound = nullptr;
};

#endif