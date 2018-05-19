#ifndef __MODULELEVEL4_H__
#define __MODULELEVEL4_H__

#include "Module.h"
#include "Animation.h"


struct SDL_Texture;

class ModuleLevel4 : public Module
{
public:
	ModuleLevel4();
	~ModuleLevel4();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect backgroundtilemaprect;
	SDL_Rect foregroundtilemaprect;
	SDL_Rect cannon_platform;
	SDL_Rect cannon_platform_end;
	SDL_Texture* backgroundtilemap = nullptr;
	SDL_Texture* foregroundtilemap = nullptr;
	SDL_Texture* BackLavaAnim = nullptr;
	SDL_Texture* Enemies_1 = nullptr;
	Animation Back_Lava;
	Animation Front_Lava;
	Animation op_cannon;

};

#endif // __MODULELEVEL4_H__