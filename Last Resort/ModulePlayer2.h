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
	bool going_right;
	bool going_left;
	bool going_up;
	bool going_down;

	//player position at the beggining of the update
	iPoint initial_pos;

	//player position at the end of the update
	iPoint* final_pos = &position;


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
	
	iPoint cannon_position;// position of the basic shot particles
	iPoint laser_beam_position;// position of the laser beam particles

	Mix_Chunk* deathsound;
	Mix_Chunk* laser_sound;
	Mix_Chunk* powerup_sound;

	//Texture
	SDL_Texture* graphics = nullptr;

	int font_2 = -1;
	char score_text2[10];
	uint score2 = 0;


};

#endif