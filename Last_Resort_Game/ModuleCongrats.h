#ifndef __ModuleCongrats_H__
#define __ModuleCongrats_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;


class ModuleCongrats : public Module
{
public:
	ModuleCongrats();
	~ModuleCongrats();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* backgroundcongrats = nullptr;
	SDL_Rect congratsrect;
};

#endif

