#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void ModulePlayer2::Shoot();
	void OnCollision(Collider* col_1, Collider* col_2) override;

public:

	uint life = 1;
	bool p2dead = false;
	WEAPON_TYPE weapon = BASIC;
	uint weapon_level=1, weapon_fired;
	int speed = 2;
	Animation spawn;
	Animation death;
	Collider* player2collider;
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


	Mix_Chunk* deathsound;
	Mix_Chunk* laser_sound;
	Mix_Chunk* powerup_sound;

	//Texture
	SDL_Texture* graphics = nullptr;


};

#endif