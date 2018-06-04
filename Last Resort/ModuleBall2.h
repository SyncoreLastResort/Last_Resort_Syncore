#ifndef __ModuleBall2_H__
#define __ModuleBall2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h" 
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleBall.h"

//enum BALL_POSITION {
//	NONE,
//	LEFT_SIDE,
//	LEFT_TOP,
//	LEFT_BOTTOM,
//	TOP,
//	BOTTOM,
//	RIGHT_SIDE,
//	RIGHT_TOP,
//	RIGHT_BOTTOM
//};

class ModuleBall2 :public Module
{
public:
	ModuleBall2();
	~ModuleBall2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2)override;
private:
	void ModuleBall2::MoveAround();
	void ModuleBall2::BallFixed();
	void ModuleBall2::ChargeBall();
	void ModuleBall2::ReleaseBall();
	void ModuleBall2::Path();
	void ModuleBall2::ReturnBall();
	void ModuleBall2::Trail();
	void ModuleBall2::Shoot();
	BALL_POSITION ModuleBall2::getPosition();

public:
	iPoint position;


private:
	Mix_Chunk * fix_ball = nullptr;
	Mix_Chunk* unfix_ball = nullptr;
	Mix_Chunk* release_ball_sound = nullptr;
	Mix_Chunk* charge_ball_sound = nullptr;

	uint charge = 0, charge_time = 0;
	iPoint velocity = { 0,0 };
	bool fixed = false, shot_charged = false, ball_thrown = false, back_to_player = false;;

	Collider *ball2_collider;
	SDL_Texture* ball_aditional_effects = nullptr;
	Animation blueball_charging;
	Animation blueball_thrown;

	Animation* current_animation;
	Animation blueball_0;
	Animation blueball_45;
	Animation blueball_90;
	Animation blueball_135;
	Animation blueball_180;
	Animation blueball_225;
	Animation blueball_270;
	Animation blueball_315;


};
#endif // !1
