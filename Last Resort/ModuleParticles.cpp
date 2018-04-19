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

	// Explosion particle
	explosion.anim.PushBack({ 315, 369, 16, 16 });
	explosion.anim.PushBack({ 331, 369, 16, 16 });
	explosion.anim.PushBack({ 347, 369, 16, 16 });
	explosion.anim.PushBack({ 363, 369, 16, 16 });
	explosion.anim.PushBack({ 379, 369, 16, 16 });
	explosion.anim.PushBack({ 395, 369, 16, 16 });
	explosion.anim.PushBack({ 411, 369, 16, 16 });
	explosion.anim.loop = false;
	explosion.anim.speed = 1.0f;
	explosion.life = 100;


	// Explosion particle
	Laserexplosion.anim.PushBack({ 95, 241, 10, 9 });
	Laserexplosion.anim.PushBack({ 82, 239, 13, 12 });
	Laserexplosion.anim.loop = true;
	Laserexplosion.anim.speed = 0.3f;
	
	//Laserexplosion.sound = lasersound;

	
	

	//Laser particle
	laser.anim.PushBack({ 115,240,15,9 });
	laser.anim.loop = true;
	laser.anim.speed = 0.1f;
	laser.speed.x = 10;
	laser.speed.y = 0;
	laser.life = 1000;
	

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
	
	
	
	boss_grenade.anim.PushBack({ 498, 335, 14,14 });
	boss_grenade.anim.PushBack({ 484, 335, 14,14 });
	boss_grenade.anim.PushBack({ 470, 335, 14,14 });
	boss_grenade.anim.PushBack({ 456, 335, 14,14 });
	boss_grenade.anim.PushBack({ 442, 335, 14,14 });
	boss_grenade.anim.PushBack({ 428, 335, 14,14 });
	boss_grenade.anim.PushBack({ 414, 335, 14,14 });
	boss_grenade.anim.PushBack({ 400, 335, 14,14 });
	boss_grenade.anim.PushBack({ 386, 335, 14,14 });
	boss_grenade.anim.PushBack({ 372, 335, 14,14 });
	boss_grenade.anim.PushBack({ 498, 349, 14,14 });
	boss_grenade.anim.PushBack({ 484, 349, 14,14 });
	boss_grenade.anim.PushBack({ 470, 349, 14,14 });
	boss_grenade.anim.PushBack({ 456, 349, 14,14 });
	boss_grenade.anim.PushBack({ 442, 349, 14,14 });
	boss_grenade.anim.PushBack({ 428, 349, 14,14 });
	boss_grenade.anim.PushBack({ 414, 349, 14,14 });
	boss_grenade.anim.PushBack({ 400, 349, 14,14 });
	boss_grenade.anim.PushBack({ 386, 349, 14,14 });
	boss_grenade.anim.speed = 0.2;
	boss_grenade.anim.loop = false;
	boss_grenade.life = 2000;
	
	
	
	
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	//Player sprites && sounds
	Laserexplosion.texture = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	laser.texture = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	explosion.texture = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	laser.sound=  App->audio->LoadSoundEffect("assets/sounds/004.Shot_center.wav");

	//Boss 1 sprites && sounds
	boss_shot.sound = App->audio->LoadSoundEffect("assets/sounds/025.Boss_shot.wav");
	boss_shot.texture = App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	boss_explosion.texture= App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	boss_cooling.texture= App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	boss_grenade.texture = App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	boss_grenade.sound = App->audio->LoadSoundEffect("assets/sounds/029.Bomb_fall.wav");
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
			//active[i]->texture = particle.texture;
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
			if(c2->type==COLLIDER_WALL || c1->type==COLLIDER_WALL)
			App->particles->AddParticle(App->particles->explosion, active[i]->position.x, active[i]->position.y-4);

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
anim(p.anim), position(p.position), speed(p.speed),
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

