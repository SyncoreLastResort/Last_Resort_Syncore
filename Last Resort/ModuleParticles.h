#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"

#define MAX_ACTIVE_PARTICLES 150

struct SDL_Texture;
struct Collider;
//enum COLLIDER_TYPE;


struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	SDL_Texture* texture = nullptr;
	Mix_Chunk* sound = nullptr;
	Particle* end_particle = nullptr;
	iPoint * position_to_attach = nullptr;
	iPoint updated_speed;
	
	
	
	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};


class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();
	
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, iPoint *position = nullptr, iPoint velocity_ = {0,0});

private:

	Particle* active[MAX_ACTIVE_PARTICLES];
	
public:
	SDL_Texture * graphics;
	SDL_Texture * ball_effects;
	SDL_Texture * graphics2;

	//Particle laser_cannon;
	//Particle ball_trail;
	//Particle boss_shot;
	//Particle boss_explosion;
	//Particle boss_dying;
	//Particle boss_cooling;
	//Particle explosion;
	//Particle Laserexplosion;
	//Particle laser;
	//Particle enemy_explosion;
	//Particle ball_shot;
	//Particle ball2_shot;
	//Particle ball_shot_explosion;
	//Particle laser_beam;
	//Particle bomb_upwards;
	//Particle bomb_downwards;
	//Particle bomb_explosion;

	Particle laser_cannon;
	Particle blueball_trail;
	Particle redball_trail;
	Particle boss_shot;
	Particle boss_explosion;
	Particle boss_dying;
	Particle boss_cooling;
	Particle explosion;
	Particle Laserexplosion;
	Particle laser;
	Particle enemy_explosion;
	Particle ball_shot;
	Particle ball2_shot;
	Particle ball_shot_explosion;
	Particle laser_beam;
	Particle bomb_upwards;
	Particle bomb_downwards;
	Particle bomb_explosion;


	//Boss level 4
	SDL_Texture* boss4_texture;

	Particle boss4_blue_circle;
	Particle boss4_heat_ball;
	Particle boss4_small_shot;
	Particle boss4_heat_end;
	



	//Bee
	Particle BeeShot;
	Particle Cannon_shot;


};

#endif // __MODULEPARTICLES_H__