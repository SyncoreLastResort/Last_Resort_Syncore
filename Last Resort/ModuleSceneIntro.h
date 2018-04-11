#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro();
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	/*SDL_Texture* background = nullptr;
	uint fx = 0;*/

	SDL_Texture * introbackground = nullptr;
	SDL_Rect introrect;
	Mix_Music* maintrackintro = nullptr;
};

#endif // __MODULESCENEINTRO_H__