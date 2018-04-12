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
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	lasersound = App->audio->LoadSoundEffect("assets/sounds/004.Shot_center.wav");

	// Explosion particle
	explosion.anim.PushBack({315, 369, 16, 16});
	explosion.anim.PushBack({331, 369, 16, 16});
	explosion.anim.PushBack({347, 369, 16, 16 });
	explosion.anim.PushBack({363, 369, 16, 16 });
	explosion.anim.PushBack({379, 369, 16, 16 });
	explosion.anim.PushBack({395, 369, 16, 16 });
	explosion.anim.PushBack({411, 369, 16, 16 });
	explosion.anim.loop = false;
	explosion.anim.speed = 1.0f;
	

	// Explosion particle
	Laserexplosion.anim.PushBack({ 95, 241, 10, 9 });
	Laserexplosion.anim.PushBack({ 82, 239, 13, 12 });
	Laserexplosion.anim.loop = true;
	Laserexplosion.anim.speed = 0.3f;

	//Laser particle
	laser.anim.PushBack({ 115,240,15,9 });
	laser.anim.loop = true;
	laser.anim.speed = 0.1f;
	laser.speed.x = 10;
	laser.speed.y = 0;
	laser.life = 1000;

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
			App->render->Blit(App->player->graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
				App->audio->PlaySoundEffect(lasersound);
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
			if(c2->type==COLLIDER_WALL)
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
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

