#ifndef __ModuleBall_H__
#define __ModuleBall_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h" 
#include "ModuleParticles.h"
#include "ModuleTextures.h"

#define PI 3.141592653589
#define SIN_45 sqrt(2)/2
#define COS_45 sqrt(2)/2
#define SIN_30 1/2
#define COS_30 sqrt(3)/2
#define SIN_60 sqrt(3)/2
#define COS_60 1/2

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
	//move the ball around the ships when it's not thrown
	void ModuleBall::MoveAround();

	//Change the orientation of the ball
	void ModuleBall::Aim();

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

	//Bools to fix the ball
	bool fix_position, ball_fixed;

	//Color of the ball
	COLOR ball_color;

	Mix_Chunk* fix_ball=nullptr;
	Mix_Chunk* unfix_ball = nullptr;
	Mix_Chunk* release_ball_sound = nullptr;
	Mix_Chunk* charge_ball_sound = nullptr;

	uint charge=0, charge_time=0;
	iPoint velocity = { 0,0 };
	bool  shot_charged = false, ball_thrown = false, back_to_player = false;;

	Collider *ball1_collider;
	SDL_Texture* ball_aditional_effects=nullptr;
	

	//Animation we want to show
	Animation* current_animation;
	
	//Animations of the blue ball
	Animation blueball_0;
	Animation blueball_45;
	Animation blueball_90;
	Animation blueball_135;
	Animation blueball_180;
	Animation blueball_225;
	Animation blueball_270;
	Animation blueball_315;
	Animation blueball_30;
	Animation blueball_60;
	Animation blueball_120;
	Animation blueball_150;
	Animation blueball_210;
	Animation blueball_240;
	Animation blueball_40;
	Animation blueball_300;
	Animation blueball_330;

	Animation blueball_charging; //blue ball charging
	Animation blueball_thrown; // blue ball when it's thrown


	//Animations of the red ball
	Animation redball_0;
	Animation redball_45;
	Animation redball_90;
	Animation redball_135;
	Animation redball_180;
	Animation redball_225;
	Animation redball_270;
	Animation redball_315;
	Animation redball_30;
	Animation redball_60;
	Animation redball_120;
	Animation redball_150;
	Animation redball_210;
	Animation redball_240;
	Animation redball_40;
	Animation redball_300;
	Animation redball_330;

	Animation redball_charging; //red ball charging
	Animation redball_thrown; //red ball thrown

	Animation *ball_animations[32];
};
#endif // !1
