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



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleFirstBoss::ModuleFirstBoss()
{
	position = { 220, 60 };
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
	eye_opening.speed = 0.1f;
	eye_opening.loop = false;

	eye_closing.PushBack({ 430, 34, 45, 34 });
	eye_closing.PushBack({ 385, 34, 45, 34 });
	eye_closing.PushBack({ 340, 34, 45, 34 });
	eye_closing.PushBack({ 295, 34, 45, 34 });
	eye_closing.speed = 0.1f;
	eye_closing.loop = false;

}

ModuleFirstBoss::~ModuleFirstBoss()
{}

// Load assets
bool ModuleFirstBoss::Start()
{
	boss1_texture = App->textures->Load("assets/sprites/Boss_Stage1_Sprites.png");
	current_head = &Head_Idle;
	current_eye = &eye_closed;
	time = SDL_GetTicks();
	
	//eye collider - this is the one that damages the enemy
	eye_collider=App->collision->AddCollider({ position.x+20,position.y+79,25,16 }, COLLIDER_ENEMY, this);
	
	//collider for the rest of the body - numbers are similar to renders
	body_collider = App->collision->AddCollider({ position.x, position.y,95,77 }, COLLIDER_ENEMY);//body
	arm_collider = App->collision->AddCollider({ position.x-14, position.y+8,22,72 }, COLLIDER_ENEMY);//arm
	head_collider = App->collision->AddCollider({ position.x + 8, position.y - 20,48,44}, COLLIDER_ENEMY);//head
	bottom_collider = App->collision->AddCollider({ position.x + 10, position.y+95,48,18 }, COLLIDER_ENEMY);//below the eye
	return true;
}

// Unload assets
bool ModuleFirstBoss::CleanUp()
{
	LOG("Unloading player");

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
	bottom_collider->SetPos(position.x + 10, position.y + 95);

	

	Act();
	if (attack_with_body)
		Body_attack();

	if (SDL_GetTicks() - time >= 3000 && SDL_GetTicks() - time <= 3020)
	{
		Attack next_attack = static_cast<Attack>(rand() % NONE);
		if (next_attack == BODY)
		{
			attack_with_body = true;
		}
		if (next_attack == CANNON)
		{
			Shot();
		}
	}
	
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

// TODO 4: Detect collision with a wall. If so, go back to intro screen. 

void ModuleFirstBoss::OnCollision(Collider * col_1, Collider * col_2)
{
	if (vulnerable)
	{
		if (col_1->type == COLLIDER_PLAYER_SHOT || col_2->type == COLLIDER_PLAYER_SHOT)
		{
			App->boss1->Disable();
			eye_collider->rect = { 0,0 };
			body_collider->rect = { 0,0 };
		}
	}

}

void ModuleFirstBoss::Shot()
{
	//first shot
	App->particles->AddParticle(App->particles->boss_shot, position.x + 20, position.y + 74, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->boss_cooling, position.x - 20, position.y + 73, COLLIDER_NONE, 280);
	App->particles->AddParticle(App->particles->boss_explosion, position.x - 10, position.y + 59);

	time = SDL_GetTicks();
}

void ModuleFirstBoss::Body_attack()
{
	uint speed = 4;
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
			time = SDL_GetTicks();
		}
	}
}

void ModuleFirstBoss::Act()
{
	if (current_eye == &eye_opening&&current_eye->Finished())
		vulnerable = true;
	else
		vulnerable = false;
}