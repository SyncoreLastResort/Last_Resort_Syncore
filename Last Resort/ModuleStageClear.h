#ifndef MODULESTAGECLEAR_H_
#define MODULESTAGECLEAR_H_

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStageClear : public Module {

public:
	ModuleStageClear();
	~ModuleStageClear();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect graphicsrect;
	SDL_Texture* graphics = nullptr;
	Mix_Music* stageclear_Sound = nullptr;
	
};

#endif

