#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground (road & tunnel)
	ground.x = 0;
	ground.y = 0;
	ground.w = 4408;
	ground.h = 239;

	// BackBackground 
	background.x = 0;
	background.y = 0;
	background.w = 803;
	background.h = 160;

	//midback
	midback.x = 0;
	midback.y = 0;
	midback.w = 1303;
	midback.h = 160;

	//bossplace
	bossplace.x = 0;
	bossplace.y = 0;
	bossplace.w = 304;
	bossplace.h = 224;
	
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");

	if (IsEnabled() == true)
	{
		App->player->Enable();
	}
	else if (IsEnabled() == false )
	{
		App->player->Disable();
	}

	bool ret = true;
	backbackground = App->textures->Load("assets/sprites/BackBackground_Sprite.png");
	midbackground = App->textures->Load("assets/sprites/MidBackground_Sprite.png");
	road = App->textures->Load("assets/sprites/Road&Tunnel_Background.png");
	bossimg = App->textures->Load("assets/sprites/Boss_Static_Background.png");
	maintracklvl1 = App->audio->LoadMusic("assets/sounds/LRMusic.ogg");
	/*App->audio->Load("assets/sounds/LRMusic.ogg");*/
	return ret;
}

float scrollground = 0.4;
float scrollmid = 0.2;
float scrollback = 0.1;

// Update: draw background
update_status ModuleBackground::Update()
{
	bool end = false;
	
	// Draw everything --------------------------------------
	App->render->Blit(bossimg, 0, 0, &bossplace); // bossimg background
	App->render->Blit(backbackground,scrollback, 0, &background, 0.75f); // back background
	App->render->Blit(midbackground, scrollmid, 32, &midback, 0.75f); // mid background
    App->render->Blit(road, scrollground, 0, &ground); //road & tunnel

	/*if (!App->audio->isplaying)
	{
		Mix_PlayMusic(App->audio->audio[0], -1);
		App->audio->isplaying = true;
	}*/
	
	App->audio->PlayMusic(maintracklvl1, ONCE);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->background, App->menu);

	scrollground -= 0.55; 
	scrollmid -= 0.25; 
	scrollback -= 0.15; 
	

	return UPDATE_CONTINUE;
}


bool ModuleBackground::CleanUp()
{
	App->textures->Unload(backbackground);
	App->textures->Unload(midbackground);
	App->textures->Unload(road);
	App->textures->Unload(bossimg);

	App->audio->StopAudio();
	App->audio->UnloadMusic(maintracklvl1);

	/*App->audio->Unload(App->audio->audio[0]);
	App->audio->isplaying = false;*/
	LOG("Unloading background scene");

	return true;
}