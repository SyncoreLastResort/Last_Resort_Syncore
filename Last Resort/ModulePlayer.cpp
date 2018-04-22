#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_render.h"
#include "ModuleBall.h"
#include "ModulePlayer2.h"

#include<stdio.h>


ModulePlayer::ModulePlayer()
{
	graphics = nullptr;
	current_animation = nullptr;
	
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
	death.PushBack({0,16,55,17}); 
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

	//Idle animation
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

	// go downwards animation
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

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	deathsound = App->audio->LoadSoundEffect("assets/sounds/005.Death.wav");
	laser_sound = App->audio->LoadSoundEffect("assets/sounds/013.Laser1_Center.wav");
	graphics = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	powerup_sound= App->audio->LoadSoundEffect("assets/sounds/018.Damage_upgrade.wav");

	death.Reset();
	spawn.Reset();
	current_animation = &spawn;
	position.x = 50;
	position.y = 100;
	score = 0;

	//App->ball_player1->Enable();
	
	// TODO 2: Add a collider to the player

	playercollider=App->collision->AddCollider({ position.x,position.y,32,14 }, COLLIDER_PLAYER, this);   // this = App->player																						
	

	font_score = App->fonts->Load("assets/fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_.,[]&$ ", 2);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->ball_player1->Disable();

	App->textures->Unload(graphics);
	App->audio->UnloadSoundEffect(deathsound);
	App->audio->UnloadSoundEffect(laser_sound);
	App->audio->UnloadSoundEffect(powerup_sound);
	
	if (playercollider != nullptr)
		playercollider->to_delete = true;
	
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (weapon_level == 2)
	{
		App->ball_player1->Enable();
	}
	
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN)
	{
		godmode = !godmode;
	}
	
	if (current_animation == &spawn&&current_animation->Finished())
		current_animation = &idle;
	
	if (current_animation != &death && current_animation != &spawn)
	{
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			Shoot();
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x - speed >= 0)
			{
				position.x -= speed;
				App->particles->Laserexplosion.position.x -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x + speed <= SCREEN_WIDTH - 32)   //32 is the ship's width
			{
				position.x += speed;
				App->particles->Laserexplosion.position.x += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
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
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP)
		{
			if (current_animation == &downwards)
			{
				downwardstoidle.Reset();
				current_animation = &downwardstoidle;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
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
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP)
		{
			if (current_animation == &upwards)
			{
				upwardstoidle.Reset();
				current_animation = &upwardstoidle;
			}
		}
		
	}
	// TODO 3: Update collider position to player position

	playercollider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	if (current_animation == &spawn)
	{
		App->render->Blit(graphics, position.x - 32, position.y - 7, &(current_animation->GetCurrentFrame()));
	}
	else if (current_animation == &death)
	{
		App->render->Blit(graphics, position.x - 23, position.y - 5, &(current_animation->GetCurrentFrame()));
	}
	else
	{
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	
	if (current_animation == &death &&current_animation->Finished() && App->player2->IsEnabled()==false)
	{
		App->fade->FadeToBlack((Module*)App->level1, (Module *)App->gameover);
		App->player->Disable();
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(score_text, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(0, 25, font_score, score_text);

	return UPDATE_CONTINUE;
}

// TODO 4: Detect collision with a wall. If so, go back to intro screen.

void ModulePlayer::OnCollision(Collider * col_1, Collider * col_2) 
{
	if (!godmode)
	{
		if (col_1->type == COLLIDER_WALL || col_2->type == COLLIDER_WALL || col_1->type == COLLIDER_ENEMY || col_2->type == COLLIDER_ENEMY || col_1->type == COLLIDER_ENEMY_SHOT || col_2->type == COLLIDER_ENEMY_SHOT || col_1->type == COLLIDER_BOSS || col_2->type == COLLIDER_BOSS || col_1->type == COLLIDER_BOSS_SHOT || col_2->type == COLLIDER_BOSS_SHOT)
		{
			if (col_1->type != COLLIDER_POWERUP && col_2->type!=COLLIDER_POWERUP)
			{
			
				if (current_animation != &death)
				{
					p1dead = true;
					weapon_level = 1;
					App->audio->PlaySoundEffect(deathsound);
					current_animation = &death;
				}
			}
		}
	}
	if (col_1->type == COLLIDER_POWERUP || col_2->type == COLLIDER_POWERUP)
		App->audio->PlaySoundEffect(powerup_sound);
}

void ModulePlayer::Shoot()
{
	
		/*App->particles->AddParticle(App->particles->Laserexplosion, App->player->position.x + 32, App->player->position.y);*/
		App->particles->AddParticle(App->particles->laser, position.x + 35, position.y + 4, COLLIDER_PLAYER_SHOT);

		if (SDL_GetTicks() - weapon_fired)
		{
			if (weapon == LASER_BEAM && weapon_level == 3 && SDL_GetTicks() - weapon_fired >= 1000)
			{

				App->audio->PlaySoundEffect(laser_sound);
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

			if (weapon == BOMB && weapon_level == 3 && SDL_GetTicks() - weapon_fired >= 1000)
			{
				App->particles->AddParticle(App->particles->bomb_downwards, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->bomb_upwards, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT);
				weapon_fired = SDL_GetTicks();
			}
			
		}
}
