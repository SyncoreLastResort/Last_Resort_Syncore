#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	idle.PushBack({ 64,0,32,14 },1);
	// go upwards animation (neo-geo sprite sheet)
	
	
	upwards.PushBack({32, 0, 32, 14},1);
	upwards.PushBack({0, 0, 32, 14},1);
	upwards.speed = 0.25f;

	// TODO 4: Make the ship go downwards with the correct animations

	downwards.PushBack({96,0,32,14},1);
	downwards.PushBack({128,0,32,14},1);
	downwards.speed = 0.25f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png"); // neo-geo version

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	
	Animation* current_animation = &idle;

	int speed = 1;
	

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &idle;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &idle;
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &upwards;

		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1 )
	{
			current_animation = &downwards;
		
		position.y += speed;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_W] == 0 )
	{
		upwards.setcurrentframe();
	}
	
	if (App->input->keyboard[SDL_SCANCODE_S] == 0)
	{
		downwards.setcurrentframe();
	}
	
	
	// Draw everything --------------------------------------
	
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}