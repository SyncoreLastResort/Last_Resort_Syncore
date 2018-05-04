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
	SDL_Rect backgroundtilemaprect;
	SDL_Texture* backgroundtilemap = nullptr;

};

#endif // __MODULELEVEL4_H__