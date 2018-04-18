#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "ModuleAudio.h"
#include "Animation.h"
#include "ModuleParticles.h"


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

	SDL_Texture* hud = nullptr;
	SDL_Texture* backbackground = nullptr;
	SDL_Texture* midbackground = nullptr;
	SDL_Texture* road = nullptr;
	SDL_Texture* bossimg = nullptr;
	SDL_Texture* background_lights = nullptr;
	Animation thin_lights;
	Animation thick_lights;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect midback;
	SDL_Rect bossplace;
	Mix_Music* maintracklvl1 = nullptr;
	float scrollground = 0.4;
	float scroll_lights = 100.0;
	float scrollmid = 0.2;
	float scrollback = 0.1;
};

#endif // __MODULELEVEL1_H__