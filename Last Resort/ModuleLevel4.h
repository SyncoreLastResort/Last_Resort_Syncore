#ifndef __MODULELEVEL4_H__
#define __MODULELEVEL4_H__

#include "Module.h"
#include "p2Point.h"

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
	SDL_Rect wallrect;
	SDL_Texture* backgroundtilemap = nullptr;
	SDL_Texture* wall = nullptr;


	//Wall Mov Down
	/*Animation WallMovDown;*/
	Collider* colliderwallmovdown = nullptr;
	bool maxreached = false;
	iPoint wallmovdownposition;
};

#endif // __MODULELEVEL4_H__