#ifndef __ModuleBall_H__
#define __ModuleBall_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h" 
#include "ModuleParticles.h"
#include "ModuleTextures.h"

#define PI 3.141592653589
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

	//Radius
	int radius = 40;

	//Angle of the ball with the ship
	float angle;

	//Angle to where the ball is aiming at
	float aim_angle;

	//Ball center
	iPoint ball_center = { 8,8 };
	//Orientative int; laps = angle/2*PI --> 
	int laps = 0;

	//Ball speed
	float rotation_speed = 2 * PI / 100;

	bool fix_position, ball_fixed;

	Mix_Chunk* fix_ball=nullptr;
	Mix_Chunk* unfix_ball = nullptr;
	Mix_Chunk* release_ball_sound = nullptr;
	Mix_Chunk* charge_ball_sound = nullptr;

	uint charge=0, charge_time=0;
	iPoint velocity = { 0,0 };
	bool  shot_charged = false, ball_thrown = false, back_to_player = false;;

	Collider *ball1_collider;
	SDL_Texture* ball_aditional_effects=nullptr;
	
	//Animations of the ball 
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
