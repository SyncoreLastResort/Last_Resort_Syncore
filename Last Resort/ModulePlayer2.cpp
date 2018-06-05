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
	spawn.PushBack({ 0, 462, 119, 25 });
	spawn.PushBack({ 139, 462, 93, 25 });
	spawn.PushBack({ 232, 462, 75, 25 });
	spawn.PushBack({ 311, 462, 74, 25 });
	spawn.PushBack({ 384, 462, 64, 25 });
	spawn.PushBack({ 448, 462, 64, 25 });
	for (int i = 0; i < 8; ++i)
		spawn.PushBack({ 0 + 64 * i,487,64,25 });
	spawn.loop = false;
	spawn.speed = 0.2f;



	//Death animation
	death.PushBack({ 0,386,64,24 });
	death.PushBack({ 64,386,64,24 });
	death.PushBack({ 128,386,64,24 });
	death.PushBack({ 458,386,64,24 });

	for (int i = 0; i<8; ++i)
		death.PushBack({ 0 + i * 64,410,64,24 });
	for (int i = 0; i<8; ++i)
		death.PushBack({ 0 + i * 64,434,64,28 });
	death.loop = false;
	death.speed = 0.3f;

	idle.PushBack({ 0,367,32,14 });
	// go upwards animation (neo-geo sprite sheet)


	upwards.PushBack({ 96, 367, 32, 14 });
	upwards.PushBack({ 129, 367, 32, 14 });
	upwards.speed = 0.1f;
	upwards.loop = false;
	//Animation when the ship stops going up 
	upwardstoidle.PushBack({ 96, 367, 32, 14 });
	upwardstoidle.PushBack({ 0,367,32,14 });
	upwardstoidle.speed = 0.1f;
	upwardstoidle.loop = false;
	// TODO 4: Make the ship go downwards with the correct animations

	downwards.PushBack({ 32,367,32,14 });
	downwards.PushBack({ 64,367,32,14 });
	downwards.speed = 0.1f;
	downwards.loop = false;
	//Animation when the ship stops going down
	downwardstoidle.PushBack({ 64,367,32,14 });
	downwardstoidle.PushBack({ 0,367,32,14 });
	downwardstoidle.speed = 0.1f;
	downwardstoidle.loop = false;


}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");

	position.x = App->render->camera.x + 50;
	death.Reset();
	spawn.Reset();
	current_animation = &spawn;
	player2collider = App->collision->AddCollider({ position.x,position.y,32,14 }, COLLIDER_PLAYER2, this);
	score2 = 0;

	deathsound = App->audio->LoadSoundEffect("assets/sounds/005.Death.wav");
	laser_sound = App->audio->LoadSoundEffect("assets/sounds/013.Laser1_Center.wav");
	graphics = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	powerup_sound = App->audio->LoadSoundEffect("assets/sounds/018.Damage_upgrade.wav");
	laser3_sound = App->audio->LoadSoundEffect("assets/sounds/015.Laser3_Center.wav");
	/*App->player->font_2 = App->player->font_score;*/

	font_2 = App->fonts->Load("assets/fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_.,[]&$ ", 2);
	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	if (player2collider != nullptr)
		player2collider->to_delete = true;
	App->ball_player2->Disable();
	App->audio->UnloadSoundEffect(laser3_sound);
	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	initial_pos = position;
	App->ball_player2->Enable();

	if (weapon_level == 2)
	{
		App->ball_player2->Enable();
	}

	if (current_animation == &spawn && current_animation->Finished())
		current_animation = &idle;

	if (current_animation != &death && current_animation != &spawn)
	{
		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
		{
			Shoot();
		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x - speed >= App->render->camera.x)
			{
				position.x -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x + speed <= App->render->camera.x + App->render->camera.w - 32)   //32 is the ship's width
			{
				position.x += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			if (position.y + speed <= SCREEN_HEIGHT - 14)
			{
				position.y += speed;
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

	//update the position of the cannon
	cannon_position.x = position.x + 32;
	cannon_position.y = position.y - 3;
	laser_position.x = position.x + 16;
	laser_position.y = position.y - 17;

	laser_beam_position.x = position.x + 32;
	laser_beam_position.y = position.y + 1;

	// Draw everything --------------------------------------
	player2collider->SetPos(position.x, position.y);
	if (current_animation == &spawn)
	{
		App->render->Blit(graphics, position.x - 32, position.y - 7, &(current_animation->GetCurrentFrame())); //We adjust the position of the drawing because of the size of the sprite
	}
	else if (current_animation == &death)
	{
		App->render->Blit(graphics, position.x - 32, position.y - 8, &(current_animation->GetCurrentFrame()));//We adjust the position of the drawing because of the size of the sprite
	}
	else
	{
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	if (current_animation == &death && current_animation->Finished())
	{
		App->player2->Disable();
		player2collider->rect = { 0,0 };
		position = { 50,100 };
	}

	sprintf_s(score_text2, 10, "%7d", score2);

	App->fonts->BlitText(50, 25, font_2, score_text2);

	if (final_pos->x > initial_pos.x)
	{
		going_left = false;
		going_right = true;
	}
	else if (final_pos->x < initial_pos.x)
	{
		going_right = false;
		going_left = true;
	}
	else if (final_pos->x == initial_pos.x)
	{
		going_right = false;
		going_left = false;
	}

	if (final_pos->y > initial_pos.y)
	{
		going_up = false;
		going_down = true;
	}
	else if (final_pos->y < initial_pos.y)
	{
		going_down = false;
		going_up = true;
	}
	else if (final_pos->y == initial_pos.y)
	{
		going_down = false;
		going_up = false;
	}

	return UPDATE_CONTINUE;
}
void ModulePlayer2::OnCollision(Collider * col_1, Collider * col_2)
{
	if (!App->player->godmode)
	{
		if ((col_1->type == COLLIDER_WALL || col_2->type == COLLIDER_WALL || col_1->type == COLLIDER_ENEMY || col_2->type == COLLIDER_ENEMY || col_1->type == COLLIDER_ENEMY_SHOT || col_2->type == COLLIDER_ENEMY_SHOT || col_1->type == COLLIDER_BOSS || col_2->type == COLLIDER_BOSS || col_1->type == COLLIDER_BOSS_SHOT || col_2->type == COLLIDER_BOSS_SHOT))
		{

			if (current_animation != &death)
			{
				p2dead = true;
				weapon_level = 1;
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
	/*App->particles->AddParticle(App->particles->Laserexplosion, position.x + 32, position.y);*/
	App->particles->AddParticle(App->particles->laser, position.x + 35, position.y + 4, COLLIDER_PLAYER2_SHOT);

	App->particles->AddParticle(App->particles->Laserexplosion, position.x + 35, position.y + 4, COLLIDER_NONE, 0, &cannon_position);
	App->particles->AddParticle(App->particles->Laserexplosion, position.x + 35, position.y + 4, COLLIDER_NONE, 150, &cannon_position);

	if (SDL_GetTicks() - weapon_fired)
	{
		if (weapon == LASER_BEAM && weapon_level >= 3 && SDL_GetTicks() - weapon_fired >= 1000)
		{
			if (weapon_level == 3)
				App->audio->PlaySoundEffect(laser_sound);
			else if (weapon_level > 3)
				App->audio->PlaySoundEffect(laser3_sound);

			App->particles->AddParticle(App->particles->laser_cannon, position.x + 35, position.y + 4, COLLIDER_NONE, 0, &laser_beam_position);

			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT, 20);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT, 40);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT, 60);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT, 80);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT, 100);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT, 120);
			App->particles->AddParticle(App->particles->laser_beam, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT, 140);

			weapon_fired = SDL_GetTicks();
			if (weapon_level > 3)
			{
				App->particles->AddParticle(App->particles->laser3_shot, laser_position.x, laser_position.y, COLLIDER_PLAYER_SHOT, 70);
				App->particles->AddParticle(App->particles->laser3_spawn, position.x + 35, position.y + 4, COLLIDER_NONE, 0, &laser_position);
				App->particles->AddParticle(App->particles->laser3_shot, laser_position.x, laser_position.y, COLLIDER_PLAYER_SHOT, 110);
				App->particles->AddParticle(App->particles->laser3_spawn, position.x + 35, position.y + 4, COLLIDER_NONE, 40, &laser_position);
				App->particles->AddParticle(App->particles->laser3_shot, laser_position.x, laser_position.y, COLLIDER_PLAYER_SHOT, 150);
				App->particles->AddParticle(App->particles->laser3_spawn, position.x + 35, position.y + 4, COLLIDER_NONE, 80, &laser_position);
				App->particles->AddParticle(App->particles->laser3_shot, laser_position.x, laser_position.y, COLLIDER_PLAYER_SHOT, 190);
				App->particles->AddParticle(App->particles->laser3_spawn, position.x + 35, position.y + 4, COLLIDER_NONE, 120, &laser_position);
				App->particles->AddParticle(App->particles->laser3_shot, laser_position.x, laser_position.y, COLLIDER_PLAYER_SHOT, 230);
				App->particles->AddParticle(App->particles->laser3_spawn, position.x + 35, position.y + 4, COLLIDER_NONE, 150, &laser_position);
			}
		}

		if (weapon == BOMB && weapon_level >= 3 && SDL_GetTicks() - weapon_fired >= 1000)
		{
			App->particles->AddParticle(App->particles->bomb_downwards, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT);
			App->particles->AddParticle(App->particles->bomb_upwards, position.x + 32, position.y + 6, COLLIDER_PLAYER2_SHOT);
			weapon_fired = SDL_GetTicks();

			if (weapon_level > 3)
			{
				App->particles->AddParticle(App->particles->bomb_downwards, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 300);
				App->particles->AddParticle(App->particles->bomb_upwards, position.x + 32, position.y + 6, COLLIDER_PLAYER_SHOT, 300);
			}
		}

	}
}