#ifndef __MODULEINTROSCENE_H__
#define __MODULEINTROSCENE_H__

#include "Module.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleIntroScene : public Module
{
public:
	ModuleIntroScene();
	~ModuleIntroScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * introbackground = nullptr;
	SDL_Rect introrect;
	Mix_Music* maintrackintro = nullptr;
};

#endif // __MODULESCENESPACE_H__
