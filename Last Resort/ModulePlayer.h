#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

enum WEAPON_TYPE
{
	LASER_BEAM, 
	BOMB,
	BASIC
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool p1dead = false;
	bool Start();
	update_status Update();
	bool CleanUp();
	void ModulePlayer::Shoot();
	void OnCollision(Collider* col_1, Collider* col_2) override;

	
public:
	
	//Booleans for the ball movement
	bool going_right;
	bool going_left;
	bool going_up;
	bool going_down;
	
	//player position at the beggining of the update
	iPoint initial_pos;

	//player position at the end of the update
	iPoint* final_pos=&position;

	WEAPON_TYPE weapon = BASIC;
	uint weapon_level = 1, weapon_fired;

	Mix_Chunk* powerup_sound;
	
	iPoint position;

	iPoint cannon_position;// position of the basic shot particles
	iPoint laser_beam_position;// position of the laser beam particles

	//god mode
	bool godmode = false;
	//FX
	Mix_Chunk* deathsound;
	Mix_Chunk* laser_sound;
	//Move speed
	int speed = 2;
	//Fonts
	int font_score = -1;
	/*int font_2 = -1;*/
	char score_text[10];
	/*char score_text2[10];*/
	uint score = 0;
	/*uint score2 = 0;*/
	/*uint fontt2 = 0;*/

	//Collider
	Collider * playercollider;

	//Texture
	SDL_Texture* graphics = nullptr;

	//Rect
	SDL_Rect ship;

	//Animations
	Animation spawn;
	Animation death;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation upwards;
	Animation downwards;
	Animation upwardstoidle;
	Animation downwardstoidle;

	//Position
	

};

#endif