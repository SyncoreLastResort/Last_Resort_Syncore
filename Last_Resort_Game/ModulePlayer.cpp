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

	idle.PushBack({ 64,0,32,14 });
	// go upwards animation (neo-geo sprite sheet)
	
	
	upwards.PushBack({32, 0, 32, 14});
	upwards.PushBack({0, 0, 32, 14});
	upwards.speed = 0.25f;

	//Animation when the ship stops going up 
	upwardstoidle.PushBack({ 32, 0, 32, 14 }, 1);
	upwardstoidle.PushBack({ 64,0,32,14 }, 1);
	upwardstoidle.speed = 0.25f;
	// TODO 4: Make the ship go downwards with the correct animations

<<<<<<< HEAD

	downwards.PushBack({96,0,32,14},1);
	downwards.PushBack({128,0,32,14},1);
=======
	downwards.PushBack({96,0,32,14});
	downwards.PushBack({128,0,32,14});
>>>>>>> eb8f3406203e664b9be2516e6856b6e4eade7c99
	downwards.speed = 0.25f;

	//Animation when the ship stops going down
	downwardstoidle.PushBack({ 96,0,32,14 }, 1);
	downwardstoidle.PushBack({ 64,0,32,14 }, 1);
	downwardstoidle.speed = 0.25f;
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
		if (position.x + speed <= SCREEN_WIDTH - 32) {
			position.x += speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &idle;
		if (position.x - speed >= 0) {
			position.x -= speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &upwards;
<<<<<<< HEAD

		position.y -= speed;

		upwardstoidle.setcurrentframe();
		goingup = true;
		goingdown = false;
=======
		if (position.y - speed >= 14) {
			position.y -= speed;
		}
>>>>>>> eb8f3406203e664b9be2516e6856b6e4eade7c99
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1 )
	{
		current_animation = &downwards;
<<<<<<< HEAD
		
		position.y += speed;

		downwardstoidle.setcurrentframe();
		goingdown = true;
		goingup = false;
=======
		if (position.y + speed <= SCREEN_HEIGHT) {
			position.y += speed;
		}
>>>>>>> eb8f3406203e664b9be2516e6856b6e4eade7c99
	}
	
	if (App->input->keyboard[SDL_SCANCODE_W] == 0 && goingup)
	{
		upwards.setcurrentframe();
		current_animation = &upwardstoidle;
		
	}
	
	if (App->input->keyboard[SDL_SCANCODE_S] == 0 && goingdown)
	{
		downwards.setcurrentframe();
		current_animation = &downwardstoidle;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_W] && App->input->keyboard[SDL_SCANCODE_S])
	{
		current_animation = &idle;
	}
	
	// Draw everything --------------------------------------
	
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}