#ifndef __ModuleBall_H__
#define __ModuleBall_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h" 
#include "ModuleParticles.h"
#include "ModuleTextures.h"

#define PI 3.141592653589
#define SIN_45 sqrt(2) / 2
#define COS_45 sqrt(2) / 2
#define SIN_30 1 / 2
#define COS_30 sqrt(3) / 2
#define SIN_60 sqrt(3) / 2
#define COS_60 1 / 2

enum COLOR {
	RED,
	BLUE
	
};
enum BALL_POSITION {
	NONE,
	LEFT_SIDE,
	LEFT_TOP,
	LEFT_BOTTOM,
	TOP,
	BOTTOM,
	RIGHT_SIDE,
	RIGHT_TOP,
	RIGHT_BOTTOM
};
class ModuleBall :public Module
{
public:
	ModuleBall();
	~ModuleBall();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2)override;
private:
	void ModuleBall::MoveAround();
	void ModuleBall::BallFixed();
	void ModuleBall::ChargeBall();
	void ModuleBall::ReleaseBall();
	void ModuleBall::Path();
	void ModuleBall::ReturnBall();
	void ModuleBall::Trail();
	void ModuleBall::Shoot();
	BALL_POSITION ModuleBall::getPosition();

public:
	iPoint position;
	
	
private:
	Mix_Chunk* fix_ball=nullptr;
	Mix_Chunk* unfix_ball = nullptr;
	Mix_Chunk* release_ball_sound = nullptr;
	Mix_Chunk* charge_ball_sound = nullptr;

	uint charge=0, charge_time=0;
	iPoint velocity = { 0,0 };
	bool fixed = false, shot_charged = false, ball_thrown = false, back_to_player = false;;

	Collider *ball1_collider;
	SDL_Texture* ball_aditional_effects=nullptr;
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
