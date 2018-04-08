#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleLevel2.h"
#include "ModuleLevel1.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleLevel1::ModuleLevel1()
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

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading background assets");

	if (IsEnabled() == true)
	{
		App->player->Enable();
	}
	else if (IsEnabled() == false)
	{
		App->player->Disable();
	}

	bool ret = true;
	backbackground = App->textures->Load("assets/sprites/BackBackground_Sprite.png");
	midbackground = App->textures->Load("assets/sprites/MidBackground_Sprite.png");
	road = App->textures->Load("assets/sprites/Road&Tunnel_Background.png");
	bossimg = App->textures->Load("assets/sprites/Boss_Static_Background.png");
	maintracklvl1 = App->audio->LoadMusic("assets/sounds/2. Jack to the metro (Stage 1).ogg");
	
	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	
	App->textures->Unload(backbackground);
	App->textures->Unload(midbackground);
	App->textures->Unload(road);
	App->textures->Unload(bossimg);

	App->audio->StopAudio();
	App->audio->UnloadMusic(maintracklvl1);

	
	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(bossimg, 0, 0, &bossplace); // bossimg background
	App->render->Blit(backbackground, scrollback, 0, &background, 0.75f); // back background
	App->render->Blit(midbackground, scrollmid, 32, &midback, 0.75f); // mid background
	App->render->Blit(road, scrollground, 2,&ground); //road & tunnel
												
	App->audio->PlayMusic(maintracklvl1, ONCE);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->level1, App->level2);

	scrollground -= 0.55;
	scrollmid -= 0.25;
	scrollback -= 0.15;
	
	return UPDATE_CONTINUE;
}