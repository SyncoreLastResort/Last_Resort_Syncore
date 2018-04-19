
#ifndef __ModuleFirstBoss_H__
#define __ModuleFirstBoss_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Collider;

class ModuleFirstBoss : public Module
{
public:
	ModuleFirstBoss();
	~ModuleFirstBoss();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* col_1, Collider* col_2) override;
private:
	void ModuleFirstBoss::Shot();
	void ModuleFirstBoss::Act();
	void ModuleFirstBoss::Body_attack();

public:
	bool vulnerable = false; //if the eye is opened, this is true and the enemy can get damaged
	enum Attack {
		CANNON, 
		BODY, 
		NONE
	};
	Collider * body_collider = nullptr;
	Collider * arm_collider = nullptr;
	Collider * head_collider = nullptr;
	Collider * eye_collider = nullptr;
	Collider * bottom_collider = nullptr;
	SDL_Texture* boss1_texture;
	iPoint position;
	Animation Arm;
	Animation Head_Idle;
	Animation Head_Open;
	Animation Head_Close;
	Animation * current_head = nullptr;
	Animation Body;
	Animation Engine;
	Animation eye_opening;
	Animation eye_closing;
	Animation eye_closed;
	Animation * current_eye = nullptr;
private:
	bool attack_with_body = false,forward = true, backward = false; // booleans for the body attack;

};

#endif