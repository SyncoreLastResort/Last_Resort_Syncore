#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* col_1, Collider* col_2) override;

public:

	Mix_Chunk* deathsound;
	Animation spawn;
	Animation death;
	Collider * playercollider;
	SDL_Texture* graphics = nullptr;
	SDL_Rect ship;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation upwards;
	Animation downwards;
	Animation upwardstoidle;
	Animation downwardstoidle;
	iPoint position;

};

#endif