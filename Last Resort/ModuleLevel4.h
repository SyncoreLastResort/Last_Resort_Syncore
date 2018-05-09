#ifndef __MODULELEVEL4_H__
#define __MODULELEVEL4_H__

#include "Module.h"


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

  	SDL_Rect backgroundrect;
	SDL_Rect foregroundrect;
	SDL_Texture* background = nullptr;
	SDL_Texture* foreground = nullptr;
	Animation Back_lava;
	Animation Fore_lava;

};

#endif // __MODULELEVEL4_H__