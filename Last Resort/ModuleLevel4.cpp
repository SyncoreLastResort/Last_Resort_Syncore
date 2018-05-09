#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleLevel4.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"


ModuleLevel4::ModuleLevel4()
{
	//Background 
    backgroundrect.x = 0;
    backgroundrect.y = 0;
    backgroundrect.w = 4143;
    backgroundrect.h = 223;

	//Foreground
	foregroundrect.x = 0;
	foregroundrect.y = 0;
	foregroundrect.w = 4143;
	foregroundrect.h = 223;

	//Background Lava Animation
	Back_lava.PushBack();
	Back_lava.PushBack();
	Back_lava.PushBack();
	Back_lava.PushBack();
	Back_lava.PushBack();
	
}

ModuleLevel4::~ModuleLevel4()
{}

// Load assets
bool ModuleLevel4::Start()
{
	LOG("Loading level4 scene");

	background = App->textures->Load("assets\sprites\Background.png");
	foreground = App->textures->Load("assets\sprites\Foreground.png");

	App->player->p1dead = false;
	App->player2->p2dead = false;
	App->player2->life = 1;

	App->player->Enable();


	return true;
}

// UnLoad assets
bool ModuleLevel4::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);

	App->player->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel4::Update()
{
	// Move camera forward -----------------------------
	App->render->camera.x += 1 * SCREEN_SIZE;
	


	if (App->player->IsEnabled() == false && App->player2->IsEnabled() == false)
	{
		App->fade->FadeToBlack(this, App->gameover);
	}

	if (App->player2->IsEnabled() == true && App->player->p1dead == true)
	{
		App->player->current_animation = &App->player->death;
		if (App->player->current_animation->Finished() == true)
			App->player->Disable();
	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, App->stageclear);
	}

	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, App->gameover);
	}


	App->player->position.x += 1;

		
	// Draw everything --------------------------------------

	App->render->Blit(background, 0, 0, &Back_lava.GetCurrentFrame(), 0.75); //background
	App->render->Blit(foreground, 0, 0, &foregroundrect, 0.75); //foreground


	if (App->input->keyboard[SDL_SCANCODE_F4] == 1)
	{
		if (App->player2->life != 0)
		{
			App->player2->Enable();
			App->player2->life -= 1;
		}
	}

	return UPDATE_CONTINUE;
}