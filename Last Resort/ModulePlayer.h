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
	//god mode
	bool godmode = false;
	//FX
	Mix_Chunk* deathsound;

	//Fonts
	int font_score = -1;
	int font_2 = -1;
	char score_text[10];
	char score_text2[10];
	uint score = 0;
	uint score2 = 0;
	uint fontt2 = 0;

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
	iPoint position;

};

#endif