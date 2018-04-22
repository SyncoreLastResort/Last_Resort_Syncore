#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;


	bomb.anim.PushBack({0,303,16,16});
	bomb.anim.PushBack({ 16,303,16,16 });
	bomb.anim.PushBack({ 32,303,16,16 });
	bomb.anim.speed = 0.1;
	bomb.anim.loop = false;
	bomb.life = 1750;
	bomb.speed = { 1,2 };

	//Laser beam
	laser_beam.anim.PushBack({ 47, 245, 16,3 });
	laser_beam.anim.loop = true;
	laser_beam.speed = { 6,0 };
	laser_beam.life = 1000;
	
	//ball trail
	ball_trail.anim.PushBack({ 251,1,32,32 });
	ball_trail.anim.PushBack({ 283,1,32,32 });
	ball_trail.anim.PushBack({ 315,1,32,32 });
	ball_trail.anim.PushBack({ 347,1,32,32 });
	ball_trail.anim.loop = false;
	ball_trail.anim.speed = 0.5;
	ball_trail.speed = { 0,0 };
	
	//Ball green shot
	ball_shot.anim.PushBack({103,252,13, 13});
	ball_shot.anim.PushBack({ 117,252,13, 13 });
	ball_shot.anim.loop = true;
	ball_shot.anim.speed = 0.5f;
	ball_shot.speed = { 0,0 };
	ball_shot.life = 650;
	ball_shot.end_particle = &ball_shot_explosion;

	//Ball2 green shot
	ball2_shot.anim.PushBack({ 103,252,13, 13 });
	ball2_shot.anim.PushBack({ 117,252,13, 13 });
	ball2_shot.anim.loop = true;
	ball2_shot.anim.speed = 0.5f;
	ball2_shot.speed = { 0,0 };
	ball2_shot.life = 2000;
	ball2_shot.end_particle = &ball_shot_explosion;

	//green shot explosion
	for (int i = 0; i < 7; ++i)
		ball_shot_explosion.anim.PushBack({ 203 + i * 16,371,16,16 });
	ball_shot_explosion.anim.speed = 1.0f;
	
	// Explosion particle
	explosion.anim.PushBack({ 315, 371, 16, 16 });
	explosion.anim.PushBack({ 331, 371, 16, 16 });
	explosion.anim.PushBack({ 347, 371, 16, 16 });
	explosion.anim.PushBack({ 363, 371, 16, 16 });
	explosion.anim.PushBack({ 379, 371, 16, 16 });
	explosion.anim.PushBack({ 395, 371, 16, 16 });
	explosion.anim.PushBack({ 411, 371, 16, 16 });
	explosion.anim.loop = false;
	explosion.anim.speed = 1.0f;
	explosion.life = 100;

	// Explosion particle
	Laserexplosion.anim.PushBack({ 95, 241, 10, 9 });
	Laserexplosion.anim.PushBack({ 82, 239, 13, 12 });
	Laserexplosion.anim.loop = false;
	Laserexplosion.anim.speed = 0.5f;

	//Laser particle
	laser.anim.PushBack({ 115,244,15,7});
	laser.anim.loop = true;
	laser.anim.speed = 0.1f;
	laser.speed.x = 7;
	laser.speed.y = 0;
	laser.life = 650;
	laser.end_particle = &explosion;
	
	boss_dying.anim.PushBack({ 286, 347, 16, 16 });
	boss_dying.anim.PushBack({ 302, 347, 22, 22 });
	boss_dying.anim.PushBack({ 324, 347, 27, 27 });
	boss_dying.anim.PushBack({ 351, 347, 28, 28 });
	boss_dying.anim.PushBack({ 379, 347, 34, 34 });
	boss_dying.anim.PushBack({ 413, 347, 34, 34 });
	boss_dying.anim.PushBack({ 447, 347, 34, 34 });
	boss_dying.anim.PushBack({ 0, 396, 34, 34 });
	boss_dying.anim.PushBack({ 34, 396, 34, 34 });
	boss_dying.anim.PushBack({ 68, 396, 34, 34 });
	boss_dying.anim.PushBack({ 102, 396, 34, 34 });
	boss_dying.anim.PushBack({ 136, 396, 34, 34 });
	boss_dying.anim.speed = 0.7;
	boss_dying.speed.x = -0.5;
	boss_dying.anim.loop = false;

	boss_shot.anim.PushBack({256,256, 63, 32});
	boss_shot.anim.PushBack({ 319,256, 63, 32 });
	boss_shot.anim.speed = 0.1;
	boss_shot.speed.x = -4;
	boss_shot.anim.loop = true;
	boss_shot.life = 1000;

	boss_explosion.anim.PushBack({ 448, 255, 64, 56 });
	boss_explosion.anim.PushBack({ 384, 255, 64, 56 });
	boss_explosion.anim.speed = 0.15;

	boss_cooling.anim.PushBack({63,311,56, 28 });
	boss_cooling.anim.PushBack({ 119,311,56, 28 });
	boss_cooling.anim.PushBack({ 175,311,56, 28 });
	boss_cooling.anim.PushBack({ 231,311,56, 28 });
	boss_cooling.anim.PushBack({ 288,311,55, 28 });
	boss_cooling.anim.PushBack({ 347,311,52, 28 });
	boss_cooling.anim.PushBack({ 407,311,48, 28 });
	boss_cooling.anim.PushBack({ 467,311,46, 28 });
	boss_cooling.anim.speed = 0.2;
	boss_cooling.anim.loop = false;
	boss_cooling.speed.x = -0.5;

	enemy_explosion.anim.PushBack({ 286, 347, 16, 16 });
	enemy_explosion.anim.PushBack({ 302, 347, 22, 22 });
	enemy_explosion.anim.PushBack({ 324, 347, 27, 27 });
	enemy_explosion.anim.PushBack({ 351, 347, 28, 28 });
	enemy_explosion.anim.PushBack({ 379, 347, 34, 34 });
	enemy_explosion.anim.PushBack({ 413, 347, 34, 34 });
	enemy_explosion.anim.PushBack({ 447, 347, 34, 34 });
	enemy_explosion.anim.PushBack({ 0, 396, 34, 34 });
	enemy_explosion.anim.PushBack({ 34, 396, 34, 34 });
	enemy_explosion.anim.PushBack({ 68, 396, 34, 34 });
	enemy_explosion.anim.PushBack({ 102, 396, 34, 34 });
	enemy_explosion.anim.PushBack({ 136, 396, 34, 34 });
	enemy_explosion.anim.speed = 0.7;
	enemy_explosion.speed.x = -0.5;
	enemy_explosion.anim.loop = false;


}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	//Player sprites && sounds
	Laserexplosion.texture = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	laser_beam.texture = Laserexplosion.texture;
	bomb.texture = Laserexplosion.texture;

	laser.texture = Laserexplosion.texture;
	explosion.texture = Laserexplosion.texture;

	laser.sound=  App->audio->LoadSoundEffect("assets/sounds/004.Shot_center.wav");

	//Ball sprites & sounds
	ball_shot.texture = Laserexplosion.texture;
	ball2_shot.texture = Laserexplosion.texture;
	ball_shot_explosion.texture= Laserexplosion.texture;

	//Boss 1 sprites && sounds
	boss_shot.sound = App->audio->LoadSoundEffect("assets/sounds/025.Boss_shot.wav");
	boss_shot.texture = App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");


	boss_explosion.texture = boss_shot.texture;
	boss_cooling.texture = boss_shot.texture;

	//Enemy sprites && sounds
	enemy_explosion.texture = App->textures->Load("assets/sprites/BossWeapons&parts_EnemyShip&structure_Multiple-effects-and-explosions.png");
	enemy_explosion.sound = App->audio->LoadSoundEffect("assets/sounds/006.Explosion1_center.wav");
	boss_dying.texture = enemy_explosion.texture;
	
	//Ball trail particles
	ball_trail.texture = App->textures->Load("assets/sprites/Ball_aditional_effects.png");
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");


	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];
		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(p->texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
				App->audio->PlaySoundEffect(p->sound);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->texture=particle.texture;
			p->sound = particle.sound;
			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			if (active[i]->end_particle != nullptr) 
			{
				AddParticle(*active[i]->end_particle, active[i]->position.x, active[i]->position.y);		
			}
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed), end_particle(p.end_particle),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		int time = ((int)SDL_GetTicks() - (int)born);
		if (time > (int)life)
			ret = false;
	}

	else
		if(anim.Finished())
			ret = false;
	if (SDL_GetTicks() >= born)
	{
		position.x += speed.x;
		position.y += speed.y;
		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}


	return ret;
}

