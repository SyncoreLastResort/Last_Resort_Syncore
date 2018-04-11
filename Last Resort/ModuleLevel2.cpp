#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleLevel2.h"
#include "ModuleCongrats.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleLevel2::ModuleLevel2()
{
	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = 3896;
	backgroundrect.h = 224;

}

ModuleLevel2::~ModuleLevel2()
{}

// Load assets
bool ModuleLevel2::Start()
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
	background2 = App->textures->Load("assets/sprites/Stage2_tilemap.png");
	maintracklvl2 = App->audio->LoadMusic("assets/sounds/5. The ruins of the metro (stage 2).ogg");

	return ret;
}

float scrollbackgroundcongrats = 0.4;

// Update: draw background
update_status ModuleLevel2::Update()
{
	bool end = false;

	// Draw everything --------------------------------------
	App->render->Blit(background2, scrollbackgroundcongrats, 0, &backgroundrect, 0.75f); // back background

	App->audio->PlayMusic(maintracklvl2, ONCE);

	if (App->input->keyboard[SDL_SCANCODE_F] == 1)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(App->level2, App->congrats);
	}
	scrollbackgroundcongrats -= 0.55;



	return UPDATE_CONTINUE;
}


bool ModuleLevel2::CleanUp()
{
	App->textures->Unload(background2);

	App->audio->StopAudio();
	App->audio->UnloadMusic(maintracklvl2);

	LOG("Unloading background scene");

	return true;
}