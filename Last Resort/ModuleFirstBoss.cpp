#include <stdlib.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFirstBoss.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel1.h"
#include "ModuleStageClear.h"


ModuleFirstBoss::ModuleFirstBoss()
{
	
	//Engine animation
	Engine.PushBack({ 240, 145, 42,32 });
	Engine.PushBack({ 282, 145, 42,32 });
	Engine.PushBack({ 324, 145, 42,32 });
	Engine.speed = 0.2f;
	Engine.loop = true;

	//Arm animation
	Arm.PushBack({0,177, 22, 72});
	Arm.PushBack({ 22,177, 22, 72 });
	Arm.PushBack({ 44,177, 22, 72 });
	Arm.PushBack({ 66,177, 22, 72 });
	Arm.speed = 0.1f;
	Arm.loop = true;

	//Head idle animtion
	Head_Idle.PushBack({0,133,48,44});
	

	//Head attack animation
	Head_Open.PushBack({ 0,133,48,44 });
	Head_Open.PushBack({ 48,133,48,44 });
	Head_Open.PushBack({ 96,133,48,44 });
	Head_Open.PushBack({ 144,133,48,44 });
	Head_Open.PushBack({ 192,133,48,44 });
	Head_Open.speed = 0.1;
	Head_Open.loop = false;


	Head_Close.PushBack({ 192,133,48,44 });
	Head_Close.PushBack({ 144,133,48,44 });
	Head_Close.PushBack({ 96,133,48,44 });
	Head_Close.PushBack({ 48,133,48,44 });
	Head_Close.PushBack({ 0,133,48,44 });
	Head_Close.speed = 0.1;
	Head_Close.loop = false;

	//Body animation
	Body.PushBack({ 96, 177, 95, 77 });
	Body.PushBack({ 191, 177, 95, 77 });
	Body.PushBack({ 286, 177, 95, 77 });
	Body.PushBack({ 381, 177, 95, 77 });
	Body.speed = 0.1;

	//Eye animations

	eye_closed.PushBack({295, 34, 45, 34});

	eye_opening.PushBack({ 340, 34, 45, 34 });
	eye_opening.PushBack({ 385, 34, 45, 34 });
	eye_opening.PushBack({ 430, 34, 45, 34 });
	eye_opening.PushBack({ 295, 0, 45, 34 });
	eye_opening.speed = 0.08f;
	eye_opening.loop = false;

	eye_closing.PushBack({ 430, 34, 45, 34 });
	eye_closing.PushBack({ 385, 34, 45, 34 });
	eye_closing.PushBack({ 340, 34, 45, 34 });
	eye_closing.PushBack({ 295, 34, 45, 34 });
	eye_closing.speed = 0.08f;
	eye_closing.loop = false;

}

ModuleFirstBoss::~ModuleFirstBoss()
{}

// Load assets
bool ModuleFirstBoss::Start()
{
	attack_with_body = false, forward = true, backward = false, boss_dead = false;

	position = { 400, 60 };
	boss1_texture = App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	current_head = &Head_Idle;
	current_eye = &eye_opening;
	boss_explosion_sound = App->audio->LoadSoundEffect("assets/sounds/020.Boss_explosion_center.wav");
	//eye collider - this is the one that damages the enemy
	eye_collider=App->collision->AddCollider({ position.x+20,position.y+79,25,19 }, COLLIDER_BOSS, this);
	
	//collider for the rest of the body - numbers are similar to renders
	body_collider = App->collision->AddCollider({ position.x, position.y,95,77 }, COLLIDER_BOSS);//body
	arm_collider = App->collision->AddCollider({ position.x-14, position.y+8,22,69 }, COLLIDER_BOSS);//arm
	head_collider = App->collision->AddCollider({ position.x + 8, position.y - 20,48,44}, COLLIDER_BOSS);//head
	bottom_collider = App->collision->AddCollider({ position.x + 21, position.y+98,48,15 }, COLLIDER_BOSS);//below the eye
	return true;
}

// Unload assets
bool ModuleFirstBoss::CleanUp()
{
	LOG("Unloading boss");
	ready = false;
	position = { 400, 60 };
	App->textures->Unload(boss1_texture);
	if (eye_collider != nullptr)
		eye_collider->to_delete = true;
	if (body_collider != nullptr)
		body_collider->to_delete = true;
	if (head_collider != nullptr)
		head_collider->to_delete = true;
	if (arm_collider != nullptr)
		arm_collider->to_delete = true;
	if (bottom_collider != nullptr)
		bottom_collider->to_delete = true;
	return true;
}


// Update: draw background
update_status ModuleFirstBoss::Update()
{
	//Update colliders position
	eye_collider->SetPos(position.x + 20, position.y + 79);
	body_collider->SetPos(position.x, position.y);
	arm_collider->SetPos(position.x - 14, position.y + 8);
	head_collider->SetPos(position.x + 8, position.y - 20);
	bottom_collider->SetPos(position.x + 21, position.y + 98);
	
	if (ready == false)
	{
		position.x -= 1;
		if (position.x <= 220)
		{
			ready = true;
		}
	}
	
	if (boss_dead == false && ready==true)
	{
		Act();

		if (SDL_GetTicks() % 2000 >= 0 && SDL_GetTicks() % 2000 <= 24)
		{
			Attack next_attack = static_cast<Attack>(rand() % NONE);
			if (next_attack == BODY)
			{
				attack_with_body = true;
			}
			else if (next_attack == CANNON)
			{
				Shot();
			}
		}
	}
	if (boss_dead == true)
		Die();
	//Body & right arm
	App->render->Blit(boss1_texture, position.x, position.y, &Body.GetCurrentFrame());
	//Head
	App->render->Blit(boss1_texture, position.x+8, position.y-20, &current_head->GetCurrentFrame());
	//Left arm
	App->render->Blit(boss1_texture, position.x -14, position.y+8, &Arm.GetCurrentFrame());
	//Engine
	App->render->Blit(boss1_texture, position.x + 6, position.y + 48, &Engine.GetCurrentFrame());
	//Eye
	App->render->Blit(boss1_texture, position.x + 10, position.y + 79, &current_eye->GetCurrentFrame());

	return UPDATE_CONTINUE;
}


void ModuleFirstBoss::OnCollision(Collider * col_1, Collider * col_2)
{
	if (vulnerable)
	{
		if (col_1->type == COLLIDER_PLAYER_SHOT || col_2->type == COLLIDER_PLAYER_SHOT|| col_1->type == COLLIDER_PLAYER2_SHOT || col_2->type == COLLIDER_PLAYER2_SHOT|| col_1->type == COLLIDER_BALL || col_2->type == COLLIDER_BALL)
		{
			if (life > 1)
				life -= 1;
			if (life==1)
			{
				Deatheffects();
				boss_dead = true;
				life -= 1;
				deathtime = SDL_GetTicks();
			}
		}
	}

}

void ModuleFirstBoss::Shot()
{
	if (current_eye == &eye_opening&&current_eye->Finished())
	{
		App->particles->AddParticle(App->particles->boss_shot, position.x + 20, position.y + 74, COLLIDER_BOSS_SHOT);
		App->particles->AddParticle(App->particles->boss_cooling, position.x - 20, position.y + 73, COLLIDER_NONE, 280);
		App->particles->AddParticle(App->particles->boss_explosion, position.x - 10, position.y + 59);

		App->particles->AddParticle(App->particles->boss_shot, position.x + 20, position.y + 74, COLLIDER_BOSS_SHOT, 500);
		App->particles->AddParticle(App->particles->boss_cooling, position.x - 20, position.y + 73, COLLIDER_NONE, 780);
		App->particles->AddParticle(App->particles->boss_explosion, position.x - 10, position.y + 59, COLLIDER_NONE, 500);
	}
}

void ModuleFirstBoss::Body_attack()
{
	uint speed = 6;
	if (current_eye == &eye_opening && current_eye->Finished())
	{
		eye_opening.Reset();
		current_eye = &eye_closing;
	}
	if (current_eye->Finished())
	{
		if (position.x <= 30 && forward)
		{
			forward = false;
			backward = true;
		}
		if (forward)
		{
			position.x-=speed;
		}
		if (backward && position.x <= 220)
		{
			position.x++;
		}
		if (backward && position.x == 220)
		{
			attack_with_body = false;
			backward = false;
			forward = true;
			current_eye = &eye_opening;
			eye_closing.Reset();
		}
	}
}

void ModuleFirstBoss::Act()
{
	if (current_eye == &eye_opening&&current_eye->Finished())
		vulnerable = true;
	else
		vulnerable = false;
	
	if (attack_with_body)
		Body_attack();
}

void ModuleFirstBoss::Deatheffects()
{
	App->audio->PlaySoundEffect(boss_explosion_sound);

	App->particles->AddParticle(App->particles->boss_dying, 220, 100);
	App->particles->AddParticle(App->particles->boss_dying, 240, 100);
	App->particles->AddParticle(App->particles->boss_dying, 220, 80);
	App->particles->AddParticle(App->particles->boss_dying, 240, 80, COLLIDER_NONE, 100);
	App->particles->AddParticle(App->particles->boss_dying, 230, 90, COLLIDER_NONE, 100);

	App->particles->AddParticle(App->particles->boss_dying, 200, 100, COLLIDER_NONE, 200);
	App->particles->AddParticle(App->particles->boss_dying, 220, 100, COLLIDER_NONE, 200);
	App->particles->AddParticle(App->particles->boss_dying, 200, 80, COLLIDER_NONE, 150);
	App->particles->AddParticle(App->particles->boss_dying, 220, 80, COLLIDER_NONE, 150);
	App->particles->AddParticle(App->particles->boss_dying, 210, 90, COLLIDER_NONE, 200);

	App->particles->AddParticle(App->particles->boss_dying, 270, 100, COLLIDER_NONE, 300);
	App->particles->AddParticle(App->particles->boss_dying, 290, 100, COLLIDER_NONE, 300);
	App->particles->AddParticle(App->particles->boss_dying, 270, 80, COLLIDER_NONE, 300);
	App->particles->AddParticle(App->particles->boss_dying, 290, 80, COLLIDER_NONE, 300);
	App->particles->AddParticle(App->particles->boss_dying, 280, 90, COLLIDER_NONE, 320);
	App->particles->AddParticle(App->particles->boss_dying, 250, 100, COLLIDER_NONE, 320);
	App->particles->AddParticle(App->particles->boss_dying, 270, 100, COLLIDER_NONE, 320);
	App->particles->AddParticle(App->particles->boss_dying, 250, 80, COLLIDER_NONE, 350);
	App->particles->AddParticle(App->particles->boss_dying, 270, 80, COLLIDER_NONE, 350);
	App->particles->AddParticle(App->particles->boss_dying, 260, 90, COLLIDER_NONE, 340);

	App->particles->AddParticle(App->particles->boss_dying, 240, 40, COLLIDER_NONE, 840);
	App->particles->AddParticle(App->particles->boss_dying, 220, 30, COLLIDER_NONE, 840);
	App->particles->AddParticle(App->particles->boss_dying, 230, 60, COLLIDER_NONE, 860);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 860);
	App->particles->AddParticle(App->particles->boss_dying, 260, 30, COLLIDER_NONE, 890);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 890);
	App->particles->AddParticle(App->particles->boss_dying, 240, 20, COLLIDER_NONE, 850);

	App->particles->AddParticle(App->particles->boss_dying, 240, 40, COLLIDER_NONE, 1040);
	App->particles->AddParticle(App->particles->boss_dying, 220, 30, COLLIDER_NONE, 1040);
	App->particles->AddParticle(App->particles->boss_dying, 230, 60, COLLIDER_NONE, 1060);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 1060);
	App->particles->AddParticle(App->particles->boss_dying, 260, 30, COLLIDER_NONE, 1090);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 1090);
	App->particles->AddParticle(App->particles->boss_dying, 240, 20, COLLIDER_NONE, 1050);

	App->particles->AddParticle(App->particles->boss_dying, 240, 40, COLLIDER_NONE, 1840);
	App->particles->AddParticle(App->particles->boss_dying, 220, 30, COLLIDER_NONE, 1840);
	App->particles->AddParticle(App->particles->boss_dying, 230, 60, COLLIDER_NONE, 1860);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 1860);
	App->particles->AddParticle(App->particles->boss_dying, 260, 30, COLLIDER_NONE, 1890);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 1890);
	App->particles->AddParticle(App->particles->boss_dying, 240, 20, COLLIDER_NONE, 1850);


	App->particles->AddParticle(App->particles->boss_dying, 220, 100, COLLIDER_NONE, 2000);
	App->particles->AddParticle(App->particles->boss_dying, 240, 100, COLLIDER_NONE, 2000);
	App->particles->AddParticle(App->particles->boss_dying, 220, 80, COLLIDER_NONE, 2000);
	App->particles->AddParticle(App->particles->boss_dying, 240, 80, COLLIDER_NONE, 2100);
	App->particles->AddParticle(App->particles->boss_dying, 230, 90, COLLIDER_NONE, 2100);

	App->particles->AddParticle(App->particles->boss_dying, 200, 100, COLLIDER_NONE, 2200);
	App->particles->AddParticle(App->particles->boss_dying, 220, 100, COLLIDER_NONE, 2200);
	App->particles->AddParticle(App->particles->boss_dying, 200, 80, COLLIDER_NONE, 2150);
	App->particles->AddParticle(App->particles->boss_dying, 220, 80, COLLIDER_NONE, 2150);
	App->particles->AddParticle(App->particles->boss_dying, 210, 90, COLLIDER_NONE, 2200);

	App->particles->AddParticle(App->particles->boss_dying, 270, 100, COLLIDER_NONE, 2300);
	App->particles->AddParticle(App->particles->boss_dying, 290, 100, COLLIDER_NONE, 2300);
	App->particles->AddParticle(App->particles->boss_dying, 270, 80, COLLIDER_NONE, 2300);
	App->particles->AddParticle(App->particles->boss_dying, 290, 80, COLLIDER_NONE, 2300);
	App->particles->AddParticle(App->particles->boss_dying, 280, 90, COLLIDER_NONE, 2320);
	App->particles->AddParticle(App->particles->boss_dying, 250, 100, COLLIDER_NONE, 2320);
	App->particles->AddParticle(App->particles->boss_dying, 270, 100, COLLIDER_NONE, 2320);
	App->particles->AddParticle(App->particles->boss_dying, 250, 80, COLLIDER_NONE,2350);
	App->particles->AddParticle(App->particles->boss_dying, 270, 80, COLLIDER_NONE,2350);
	App->particles->AddParticle(App->particles->boss_dying, 260, 90, COLLIDER_NONE, 2340);

	App->particles->AddParticle(App->particles->boss_dying, 240, 40, COLLIDER_NONE, 2840);
	App->particles->AddParticle(App->particles->boss_dying, 220, 30, COLLIDER_NONE, 2840);
	App->particles->AddParticle(App->particles->boss_dying, 230, 60, COLLIDER_NONE, 2860);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 2860);
	App->particles->AddParticle(App->particles->boss_dying, 260, 30, COLLIDER_NONE, 2890);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 2890);
	App->particles->AddParticle(App->particles->boss_dying, 240, 20, COLLIDER_NONE, 2850);

	App->particles->AddParticle(App->particles->boss_dying, 240, 40, COLLIDER_NONE, 3040);
	App->particles->AddParticle(App->particles->boss_dying, 220, 30, COLLIDER_NONE, 3040);
	App->particles->AddParticle(App->particles->boss_dying, 230, 60, COLLIDER_NONE, 3060);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 3060);
	App->particles->AddParticle(App->particles->boss_dying, 260, 30, COLLIDER_NONE, 3090);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 3090);
	App->particles->AddParticle(App->particles->boss_dying, 240, 20, COLLIDER_NONE, 3050);

	App->particles->AddParticle(App->particles->boss_dying, 240, 40, COLLIDER_NONE, 3840);
	App->particles->AddParticle(App->particles->boss_dying, 220, 30, COLLIDER_NONE, 3840);
	App->particles->AddParticle(App->particles->boss_dying, 230, 60, COLLIDER_NONE, 3860);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 3860);
	App->particles->AddParticle(App->particles->boss_dying, 260, 30, COLLIDER_NONE, 3890);
	App->particles->AddParticle(App->particles->boss_dying, 250, 50, COLLIDER_NONE, 3890);
	App->particles->AddParticle(App->particles->boss_dying, 240, 20, COLLIDER_NONE, 3850);
}

void ModuleFirstBoss::Die()
{
	if (SDL_GetTicks() - deathtime >= 200 && SDL_GetTicks() - deathtime <= 224)
		App->audio->PlaySoundEffect(boss_explosion_sound);

	if (SDL_GetTicks() - deathtime >= 500 && SDL_GetTicks() - deathtime <= 524)
		App->audio->PlaySoundEffect(boss_explosion_sound);

	if (SDL_GetTicks() - deathtime >= 1000 && SDL_GetTicks() - deathtime <= 1025)
		App->audio->PlaySoundEffect(boss_explosion_sound);

	if (SDL_GetTicks() - deathtime >= 1200 && SDL_GetTicks() - deathtime <= 1225)
		App->audio->PlaySoundEffect(boss_explosion_sound);

	if (SDL_GetTicks() - deathtime >= 1500 && SDL_GetTicks() - deathtime <= 1530)
		App->audio->PlaySoundEffect(boss_explosion_sound);

	if (SDL_GetTicks() - deathtime >= 2000 && SDL_GetTicks() - deathtime <= 2025)
		App->audio->PlaySoundEffect(boss_explosion_sound);
	
	if (SDL_GetTicks() - deathtime >= 2500 && SDL_GetTicks() - deathtime <= 2524)
		App->audio->PlaySoundEffect(boss_explosion_sound);
	
	if (SDL_GetTicks() - deathtime >= 3000 && SDL_GetTicks() - deathtime <= 3025)
		App->audio->PlaySoundEffect(boss_explosion_sound);
	
	if (SDL_GetTicks() - deathtime >= 3500 && SDL_GetTicks() - deathtime <= 3525)
		App->audio->PlaySoundEffect(boss_explosion_sound);

	if (SDL_GetTicks() - deathtime >= 4000 && SDL_GetTicks() - deathtime <= 4025)
		App->audio->PlaySoundEffect(boss_explosion_sound);

	if (SDL_GetTicks() - deathtime > 4500)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(App->level1, App->stageclear);
		eye_collider->rect = { 0,0 };
		body_collider->rect = { 0,0 };
	}
}