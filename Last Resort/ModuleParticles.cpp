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
	
	/*for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j)
			laser_cannon.anim.PushBack({ 0+i*31, 319+j*13, 31, 13 });
*/

	for (int j = 0; j < 3; ++j)
	{
		laser_cannon.anim.PushBack({ 0, 319 + j * 13, 31, 13 });
	}
	
		laser_cannon.anim.PushBack({ 0,358,31,9 });
	
	for (int j = 0; j < 3; ++j)
	{
		laser_cannon.anim.PushBack({ 31, 319 + j * 13, 31, 13 });
	}

	laser_cannon.anim.loop = false;
	laser_cannon.anim.speed = 0.3;


	bomb_downwards.anim.PushBack({0,303,16,16});
	bomb_downwards.anim.PushBack({ 16,303,16,16 });
	bomb_downwards.anim.PushBack({ 32,303,16,16 });
	bomb_downwards.anim.speed = 0.1;
	bomb_downwards.anim.loop = false;
	bomb_downwards.life = 1750;
	bomb_downwards.speed = { 1,2 };
	bomb_downwards.end_particle = &bomb_explosion;

	bomb_upwards.anim.PushBack({ 0,303,16,16 });
	bomb_upwards.anim.PushBack({ 47,303,16,16 });
	bomb_upwards.anim.PushBack({ 63,303,16,16 });
	bomb_upwards.anim.speed = 0.1;
	bomb_upwards.anim.loop = false;
	bomb_upwards.life = 1750;
	bomb_upwards.speed = { 1,-2 };
	bomb_upwards.end_particle = &bomb_explosion;

	for (int i=0;i<11;++i)
		bomb_explosion.anim.PushBack({ 448 - 32 * i, 480, 32, 32 });
	bomb_explosion.anim.loop = false;
	bomb_explosion.anim.speed = 0.5;

	//Laser beam
	laser_beam.anim.PushBack({ 47, 245, 16,3 });
	laser_beam.anim.loop = true;
	laser_beam.speed = { 6,0 };
	laser_beam.life = 1000;
	
	//ball trail
	
	blueball_trail.anim.PushBack({ 347,1,32,32 });
	blueball_trail.anim.PushBack({ 315,1,32,32 });
	blueball_trail.anim.PushBack({ 283,1,32,32 });
	blueball_trail.anim.PushBack({ 251,1,32,32 });
	
	blueball_trail.anim.loop = false;
	blueball_trail.anim.speed = 0.4;
	blueball_trail.speed = { 0,0 };
	
	redball_trail.anim.PushBack({ 0,1,32,32 });
	redball_trail.anim.PushBack({ 32,1,32,32 });
	redball_trail.anim.PushBack({ 64,1,32,32 });
	redball_trail.anim.PushBack({ 96,1,32,32 });
	
	redball_trail.anim.loop = false;
	redball_trail.anim.speed = 0.4;
	redball_trail.speed = { 0,0 };
	
	//Ball green shot
	for (int i = 0; i<4; ++i)
		ball_shot.anim.PushBack({ 87 + 14 * i,253,13, 13 });
	ball_shot.anim.loop = true;
	ball_shot.anim.speed = 0.3f;
	ball_shot.speed = { 0,0 };
	ball_shot.life = 650;
	ball_shot.end_particle = &ball_shot_explosion;

	//Ball2 green shot
	for (int i = 0; i<4; ++i)
		ball2_shot.anim.PushBack({ 87 + 14 * i,253,13, 13 });
	ball2_shot.anim.loop = true;
	ball2_shot.anim.speed = 0.5f;
	ball2_shot.speed = { 0,0 };
	ball2_shot.life = 650;
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
	Laserexplosion.anim.speed = 0.7f;

	//Laser particle
	laser.anim.PushBack({ 115,244,15,7});
	laser.anim.loop = true;
	laser.anim.speed = 0.1f;
	laser.speed.x = 7;
	laser.speed.y = 0;
	laser.life = 750;
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


	//Tracking Bee

	BeeShot.anim.PushBack({ 261,270,5,5 });
	BeeShot.anim.PushBack({ 266,270,5,5 });
	BeeShot.anim.PushBack({ 271,270,5,5 });
	BeeShot.anim.PushBack({ 276,270,5,5 });
	BeeShot.anim.loop = true;
	BeeShot.life = 3000;
	BeeShot.anim.speed = 0.2f;
	BeeShot.speed.x = 0;
	BeeShot.speed.y = 0;

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	graphics = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	graphics2= App->textures->Load("Images/Particles/BossWeapons&parts_EnemyShip&structure_Multiple-effects-and-explosions.png");
	
	//Player sprites && sounds
	laser_cannon.texture = graphics;
	Laserexplosion.texture = graphics;
	laser_beam.texture = graphics;
	bomb_downwards.texture = graphics;
	bomb_upwards.texture = graphics;
	/*laser.texture = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	explosion.texture = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");*/
	laser.texture = graphics;
	explosion.texture = graphics;

	laser.sound=  App->audio->LoadSoundEffect("assets/sounds/004.Shot_center.wav");

	//Ball sprites & sounds
	/*ball_shot.texture= App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");*/
	ball_shot.texture = graphics;
	ball2_shot.texture = graphics;
	ball_shot_explosion.texture= graphics;

	//Boss 1 sprites && sounds
	boss_shot.sound = App->audio->LoadSoundEffect("assets/sounds/025.Boss_shot.wav");
	boss_shot.texture = App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	
	/*boss_explosion.texture= App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	boss_cooling.texture= App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");*/

	boss_explosion.texture = boss_shot.texture;
	boss_cooling.texture = boss_shot.texture;

	//Enemy sprites && sounds
	enemy_explosion.texture = App->textures->Load("assets/sprites/BossWeapons&parts_EnemyShip&structure_Multiple-effects-and-explosions.png");
	enemy_explosion.sound = App->audio->LoadSoundEffect("assets/sounds/006.Explosion1_center.wav");
	boss_dying.texture = enemy_explosion.texture;

	bomb_explosion.sound = App->audio->LoadSoundEffect("assets/sounds/010.Bomb_center.wav");
	bomb_explosion.texture = enemy_explosion.texture;
	//Ball trail particles
	ball_effects = App->textures->Load("assets/sprites/Ball_aditional_effects.png");
	redball_trail.texture = ball_effects;
	blueball_trail.texture = ball_effects;
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	/*App->textures->Unload(enemy_explosion.texture);*/

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	App->textures->Unload(ball_effects);
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, iPoint *position)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->position_to_attach = position;
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
fx(p.fx), born(p.born), life(p.life), position_to_attach(p.position_to_attach)
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
		if (position_to_attach != nullptr)
			position = *position_to_attach;
		else 
		{
			position.x += speed.x;
			position.y += speed.y;
		}
		
		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}


	return ret;
}

