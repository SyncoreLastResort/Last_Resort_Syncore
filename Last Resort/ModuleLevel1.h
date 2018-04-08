#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1();
	~ModuleLevel1();

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
	float scrollground = 0.4;
	float scrollmid = 0.2;
	float scrollback = 0.1;
};

#endif // __MODULELEVEL1_H__