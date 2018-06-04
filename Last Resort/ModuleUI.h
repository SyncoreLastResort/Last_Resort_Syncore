#ifndef ModuleUI_H
#define ModuleUI_H

#include "Module.h"
//#include "SDL/include/SDL_pixels.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")


struct SDL_Texture;

class ModuleUI : public Module {

public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	Mix_Chunk *Insert_Coin = nullptr;

public:

	//Scores & UI

	//Font id
	int font = -1;

	SDL_Texture*UI_Main_Menu = nullptr;

	//Top Score
	char top_score[10];
	uint TopScore;

	//P1 Life
	char life_text[10];
	uint P1Life;

	//P2 Life
	char life2_text[10];
	uint P2Life;

	//Coins
	int coins;
	char coins_text[10];
};

#endif
