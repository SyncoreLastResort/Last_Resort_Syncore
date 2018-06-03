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
	
	SDL_Texture* background = nullptr;
	uint fx = 0;

	//SDL_Texture * introbackground = nullptr;
	//SDL_Rect introrect;
	//Mix_Music* maintrackintro = nullptr;

	SDL_Texture * introbackground = nullptr;
	SDL_Texture * black = nullptr;
	SDL_Texture * Max330 = nullptr;
	SDL_Texture * MegaPro = nullptr;
	SDL_Texture * SNK_Logo = nullptr;
	SDL_Texture * L = nullptr;
	SDL_Texture * A = nullptr;
	SDL_Texture * S = nullptr;
	SDL_Texture * T = nullptr;
	SDL_Texture * R = nullptr;
	SDL_Texture * E = nullptr;
	SDL_Texture * O = nullptr;
	SDL_Texture * lastresort = nullptr;
	SDL_Texture * Button = nullptr;
	SDL_Texture * PressStart = nullptr;

	Animation* current_animation = nullptr;
	Animation intro_neogeo;
	Animation max330;
	Animation mega_pro;
	Animation SNK;
	Animation C_sprite;
	Animation L_Anim;
	Animation A_Anim;
	Animation S_Anim;
	Animation T_Anim;
	Animation R_Anim;
	Animation E_Anim;
	Animation S2_Anim;
	Animation O_Anim;
	Animation R2_Anim;
	Animation T2_Anim;
	Animation StartButton;
	Animation LastFade;

	SDL_Rect introrect;
	Mix_Music* maintrackintro = nullptr;
	Mix_Music* neogeotrack = nullptr;

	bool endofmusic1 = false;
	bool end = false;
};

#endif // __MODULESCENEINTRO_H__