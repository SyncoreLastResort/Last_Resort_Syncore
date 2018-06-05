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

	/*SDL_Rect backgroundtilemaprect;
	SDL_Texture* backgroundtilemap = nullptr;*/


	//Background
	/*SDL_Rect backgroundrect;
	SDL_Rect foregroundrect;
	SDL_Texture* background = nullptr;
	SDL_Texture* foreground = nullptr;*/

	//Wall Mov Down
	SDL_Rect wallrect;
	SDL_Texture* wall = nullptr;
	Collider* colliderwallmovdown = nullptr;
	Collider* colliderwallmovdown2 = nullptr;
	Collider* colliderwallmovdown3 = nullptr;
	Collider* colliderwallmovdown4 = nullptr;
	Collider* colliderplatform1 = nullptr;
	Collider* colliderplatform2 = nullptr;
	Collider* colliderplatform3 = nullptr;
	Collider* colliderplatform4 = nullptr;
	Collider* colliderplatform5 = nullptr;
	Collider* colliderplatform6 = nullptr;
	Collider* colliderplatform7 = nullptr;
	bool maxreached = false;
	iPoint wallmovdownposition;
	iPoint wallmovdownposition2;
	iPoint wallmovdownposition3;
	iPoint wallmovdownposition4;

	//Pinchy Wall
	SDL_Texture* pinchywall = nullptr;
	Animation pinchywalanim;
	Collider* colliderpinchywall = nullptr;
	Collider* colliderpinchywall2 = nullptr;
	Collider* colliderpinchywall3 = nullptr;
	Collider* colliderpinchywall4 = nullptr;
	bool maxreachedpinchy = false;
	iPoint pinchywallposition;
	iPoint pinchywallposition2;
	iPoint pinchywallposition3;
	iPoint pinchywallposition4;

	//Background and foreground
	SDL_Rect backgroundtilemaprect;
	SDL_Rect foregroundtilemaprect1;
	SDL_Rect foregroundtilemaprect2;
	SDL_Rect foreground_platforms;
	SDL_Texture* backgroundtilemap = nullptr;
	SDL_Texture* foregroundtilemap1 = nullptr;
	SDL_Texture* foregroundtilemap2 = nullptr;
	SDL_Texture* foreground_platform = nullptr;
	SDL_Texture* BackLavaAnim = nullptr;
	Animation Back_Lava;
	Animation platform_up;
	Animation platform_down;
	bool platformmaxpos;
	

	//opening cannon
	SDL_Rect cannon_platform;
	SDL_Rect cannon_platform_end;
	SDL_Texture* Enemies_1 = nullptr;
	Animation op_cannon;

	bool coinisminus = false;

	bool createcollidersonce = false;

	//Background colliders

	Collider* foregroundcoll = nullptr;
	Collider* foregroundcoll2 = nullptr;
	Collider* foregroundcoll3 = nullptr;
	Collider* foregroundcoll4 = nullptr;
	Collider* foregroundcoll5 = nullptr;
	Collider* foregroundcoll6 = nullptr;
	Collider* foregroundcoll7 = nullptr;
	Collider* foregroundcoll8 = nullptr;
	Collider* foregroundcoll9 = nullptr;
	Collider* foregroundcoll10 = nullptr;
	Collider* foregroundcoll11 = nullptr;
	Collider* foregroundcoll12 = nullptr;
	Collider* foregroundcoll13 = nullptr;
	Collider* foregroundcoll14 = nullptr;
	Collider* foregroundcoll15 = nullptr;


	bool bosstime = false;
};

#endif // __MODULELEVEL4_H__