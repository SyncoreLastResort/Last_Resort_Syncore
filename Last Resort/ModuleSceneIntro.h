#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "ModuleAudio.h"
#include "Animation.h"

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
	SDL_Texture * Max330 = nullptr;
	SDL_Texture * MegaPro = nullptr;
	SDL_Texture * SNK_Logo = nullptr;
	SDL_Texture * SNK_Logo2 = nullptr;
	SDL_Texture * LastResort = nullptr;

	Animation* current_animation = nullptr;
	Animation intro_neogeo;
	Animation max330;
	Animation mega_pro;
	Animation SNK; 
	Animation C_sprite;
	
	
	SDL_Rect introrect;
	Mix_Music* maintrackintro = nullptr;
};

#endif // __MODULESCENEINTRO_H__