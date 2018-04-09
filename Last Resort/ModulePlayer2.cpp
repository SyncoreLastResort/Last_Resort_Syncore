#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 50;
	position.y = 100;

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

	graphics = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	current_animation = &idle;
	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN) {
		App->particles->AddParticle(App->particles->Laserexplosion, App->particles->Laserexplosion.position.x, App->particles->Laserexplosion.position.y);
		App->particles->AddParticle(App->particles->laser, App->player2->position.x + 35, App->player2->position.y);
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


	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y + 25);
		App->particles->AddParticle(App->particles->explosion, position.x - 25, position.y, 500);
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 25, 1000);
		App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y, 1500);
	}



	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}