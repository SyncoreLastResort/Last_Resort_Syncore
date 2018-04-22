#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleBall2.h"

#include<stdio.h>


ModulePlayer2::ModulePlayer2()
{
	current_animation = nullptr;

	position.x = 50;
	position.y = 100;
	//Spawn animation
	spawn.PushBack({ 0,137,64,25 });
	spawn.PushBack({ 0,162,64,25 });
	spawn.PushBack({ 0,187,64,25 });
	spawn.PushBack({ 0,212,64,25 });
	spawn.PushBack({ 64,137,64,25 });
	spawn.PushBack({ 64,162,64,25 });
	spawn.PushBack({ 64,187,64,25 });
	spawn.PushBack({ 64,212,64,25 });
	spawn.PushBack({ 128,125,64,25 });
	spawn.PushBack({ 128,150,64,25 });
	spawn.loop = false;
	spawn.speed = 0.2f;

	//Death animation
	death.PushBack({ 0,16,55,17 });
	death.PushBack({ 0,33,55,17 });
	death.PushBack({ 0,50,55,17 });
	death.PushBack({ 0,67,55,17 });
	death.PushBack({ 0,84,55,17 });
	death.PushBack({ 0,101,55,17 });
	death.PushBack({ 55,16,55,17 });
	death.PushBack({ 55,33,55,17 });
	death.PushBack({ 55,50,55,17 });
	death.PushBack({ 55,67,55,17 });
	death.PushBack({ 55,84,55,17 });
	death.PushBack({ 55,101,55,17 });
	death.PushBack({ 110,16,55,17 });
	death.PushBack({ 110,33,55,17 });
	death.PushBack({ 110,50,55,17 });
	death.PushBack({ 110,67,55,17 });
	death.PushBack({ 110,84,55,17 });
	death.PushBack({ 110,101,55,17 });
	death.loop = false;
	death.speed = 0.3f;

	idle.PushBack({ 64,0,32,14 });
	// go upwards animation (neo-geo sprite sheet)


	upwards.PushBack({ 32, 0, 32, 14 });
	upwards.PushBack({ 0, 0, 32, 14 });
	upwards.speed = 0.1f;
	upwards.loop = false;
	//Animation when the ship stops going up 
	upwardstoidle.PushBack({ 32, 0, 32, 14 });
	upwardstoidle.PushBack({ 64,0,32,14 });
	upwardstoidle.speed = 0.1f;
	upwardstoidle.loop = false;
	// TODO 4: Make the ship go downwards with the correct animations

	downwards.PushBack({ 96,0,32,14 });
	downwards.PushBack({ 128,0,32,14 });
	downwards.speed = 0.1f;
	downwards.loop = false;
	//Animation when the ship stops going down
	downwardstoidle.PushBack({ 96,0,32,14 });
	downwardstoidle.PushBack({ 64,0,32,14 });
	downwardstoidle.speed = 0.1f;
	downwardstoidle.loop = false;


}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");
	
	
	death.Reset();
	spawn.Reset();
	current_animation = &spawn;
	player2collider = App->collision->AddCollider({ position.x,position.y,32,14 }, COLLIDER_PLAYER2, this);
	App->player->score2 = 0;

	App->player->font_2 = App->player->font_score;
	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	if (player2collider != nullptr)
		player2collider->to_delete = true;
	App->ball_player2->Disable();
	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	if (weapon_level == 2)
	{
		App->ball_player2->Enable();
	}

	if (current_animation == &spawn && current_animation->Finished())
		current_animation = &idle;

	if (current_animation != &death && current_animation != &spawn)
	{
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN) {
			Shoot();
		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x - speed >= 0)
			{
				position.x -= speed;
				App->particles->Laserexplosion.position.x -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x + speed <= SCREEN_WIDTH - 32)   //32 is the ship's width
			{
				position.x += speed;
				App->particles->Laserexplosion.position.x += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			if (position.y + speed <= SCREEN_HEIGHT - 14)
			{
				position.y += speed;
				App->particles->Laserexplosion.position.y += speed;
			}
			if (current_animation != &downwards)
			{
				downwards.Reset();
				current_animation = &downwards;
			}
		}
		//When ship starts going down, back to idle position
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_UP)
		{
			if (current_animation == &downwards)
			{
				downwardstoidle.Reset();
				current_animation = &downwardstoidle;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
		{
			if (position.y - speed >= 2)
			{
				position.y -= speed;
				App->particles->Laserexplosion.position.y -= speed;
			}
			if (current_animation != &upwards)
			{
				upwards.Reset();
				current_animation = &upwards;
			}
		}
		//When ship starts going up, back to idle position
		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP)
		{
			if (current_animation == &upwards)
			{
				upwardstoidle.Reset();
				current_animation = &upwardstoidle;
			}
		}

	}
	// Draw everything --------------------------------------
	player2collider->SetPos(position.x, position.y);
	if (current_animation == &spawn)
	{
		App->render->Blit(App->player->graphics, position.x - 32, position.y - 7, &(current_animation->GetCurrentFrame()));
	}
	else if (current_animation == &death)
	{
		App->render->Blit(App->player->graphics, position.x - 23, position.y - 5, &(current_animation->GetCurrentFrame()));
	}
	else
	{
		App->render->Blit(App->player->graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	if (current_animation == &death && current_animation->Finished())
	{
		App->player2->Disable();
		player2collider->rect = { 0,0 };
		position = { 50,100 };
	}

	sprintf_s(App->player->score_text2, 10, "%7d", App->player->score2);

	App->fonts->BlitText(50, 25, App->player->font_2, App->player->score_text2);


	return UPDATE_CONTINUE;
}
void ModulePlayer2::OnCollision(Collider * col_1, Collider * col_2)
{
	if (!App->player->godmode)
	{
		if ((col_1->type == COLLIDER_WALL || col_2->type == COLLIDER_WALL || col_1->type == COLLIDER_ENEMY || col_2->type == COLLIDER_ENEMY || col_1->type == COLLIDER_ENEMY_SHOT || col_2->type == COLLIDER_ENEMY_SHOT|| col_1->type == COLLIDER_BOSS || col_2->type == COLLIDER_BOSS || col_1->type == COLLIDER_BOSS_SHOT || col_2->type == COLLIDER_BOSS_SHOT))
		{
			p2dead = true;
			if (current_animation != &death)
			{
				App->audio->PlaySoundEffect(App->player->deathsound);
				current_animation = &death;

			}
		}
	}
	if (col_1->type == COLLIDER_POWERUP || col_2->type == COLLIDER_POWERUP)
		App->audio->PlaySoundEffect(App->player->powerup_sound);
}

void ModulePlayer2::Shoot()
{
	App->particles->AddParticle(App->particles->Laserexplosion, position.x + 32, position.y);
	App->particles->AddParticle(App->particles->laser, position.x + 35, position.y + 4, COLLIDER_PLAYER_SHOT);

	if (SDL_GetTicks() - App->player->weapon_fired)
	{
		if (weapon == LASER_BEAM && weapon_level >= 3 && SDL_GetTicks() - weapon_fired >= 1000)
		{

			App->audio->PlaySoundEffect(App->player->laser_sound);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 20);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 40);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 60);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 80);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 100);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 120);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 140);

			weapon_fired = SDL_GetTicks();

		}

		if (weapon == BOMB && weapon_level >= 3 && SDL_GetTicks() - weapon_fired >= 1000)
		{
			App->particles->AddParticle(App->particles->bomb_downwards, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->bomb_upwards, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT);
			weapon_fired = SDL_GetTicks();
		}
		
	}
}
