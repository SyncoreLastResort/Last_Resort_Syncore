#ifndef __MODULELEVEL4_H__
#define __MODULELEVEL4_H__

#include "Module.h"
#include "p2Point.h"
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

	//Timer that tells us when the level is started
	uint start_time;
	
	//Boolean that comes true when we arrive at the boss (by time)
	bool boss_fight;

	//Music
	Mix_Music* main_track_lvl4=nullptr;
	Mix_Music* boss_track_lvl4 = nullptr;

	SDL_Rect backgroundtilemaprect;
	SDL_Rect wallrect;
	SDL_Texture* backgroundtilemap = nullptr;
	SDL_Texture* wall = nullptr;
	SDL_Texture* pinchywall = nullptr;


	//Wall Mov Down
	Collider* colliderwallmovdown = nullptr;
	bool maxreached = false;
	iPoint wallmovdownposition;

	//Pinchy Wall
	Animation pinchywalanim;
	Collider* colliderpinchywall = nullptr;
	bool maxreachedpinchy = false;
	iPoint pinchywallposition;
};

#endif // __MODULELEVEL4_H__