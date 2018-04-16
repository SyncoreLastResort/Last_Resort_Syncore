#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_timer.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;
	
	//Spawn animation
	spawn.PushBack({ 0,135,64,25 });
	spawn.PushBack({ 0,160,64,25 });
	spawn.PushBack({ 0,185,64,25 });
	spawn.PushBack({ 0,210,64,25 });
	spawn.PushBack({ 64,135,64,25 });
	spawn.PushBack({ 64,160,64,25 });
	spawn.PushBack({ 64,185,64,25 });
	spawn.PushBack({ 64,210,64,25 });
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
	graphics = App->textures->Load("assets/sprites/Ship&Ball_Sprite.png");
	death.Reset();
	spawn.Reset();
	current_animation = &spawn;
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
	
	if (playercollider != nullptr)
		playercollider->to_delete = true;
	
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 2;
	
	if (current_animation == &spawn&&current_animation->Finished())
		current_animation = &idle;
	
	if (current_animation != &death)
	{
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

	return UPDATE_CONTINUE;
}

// TODO 4: Detect collision with a wall. If so, go back to intro screen.

void ModulePlayer::OnCollision(Collider * col_1, Collider * col_2) 
{
	if (col_1->type == COLLIDER_WALL || col_2->type == COLLIDER_WALL)
	{
		if (current_animation != &death)
		{
			App->audio->PlaySoundEffect(deathsound);
			current_animation = &death;
		}
		if (current_animation->Finished()) {
			App->fade->FadeToBlack((Module*)App->level1, (Module *)App->scene_intro);
			App->player->Disable();
		}
	}
}
