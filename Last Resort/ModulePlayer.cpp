#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

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

	graphics = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	current_animation = &idle;

	position.x = 50;
	position.y = 100;

	// TODO 2: Add a collider to the player

	playercollider=App->collision->AddCollider({ position.x,position.y,32,14 }, COLLIDER_PLAYER, this);   // this = App->player

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->Laserexplosion, App->player->position.x + 32, App->player->position.y);
		App->particles->AddParticle(App->particles->laser, position.x + 35, position.y, COLLIDER_PLAYER_SHOT);
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

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	   && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	// TODO 3: Update collider position to player position

	playercollider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 4: Detect collision with a wall. If so, go back to intro screen.

void ModulePlayer::OnCollision(Collider * col_1, Collider * col_2) 
{
	if (col_1->type == COLLIDER_WALL || col_2->type == COLLIDER_WALL)
	{
		App->player->Disable();
		App->fade->FadeToBlack((Module*)App->level1, (Module *)App->scene_intro);
	}

}
