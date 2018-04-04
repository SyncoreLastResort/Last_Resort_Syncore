#ifndef __ModuleLevel2_H__
#define __ModuleLevel2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;


class ModuleLevel2 : public Module
{
public:
	ModuleLevel2();
	~ModuleLevel2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background2 = nullptr;
	SDL_Rect backgroundrect;
	Mix_Music* maintracklvl2 = nullptr;
};

#endif
