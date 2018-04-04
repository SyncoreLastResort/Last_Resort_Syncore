#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCongrats.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleCongrats::ModuleCongrats()
{
	congratsrect.x = 0;
	congratsrect.y = 0;
	congratsrect.w = 304;
	congratsrect.h = 224;

}

ModuleCongrats::~ModuleCongrats()
{}

// Load assets
bool ModuleCongrats::Start()
{
	LOG("Loading background assets");

	if (IsEnabled() == true)
	{
		App->player->Disable();
	}
	
	bool ret = true;
	backgroundcongrats = App->textures->Load("assets/sprites/GameEnd.png");

	return ret;
}

float scrollbackground = 0.4;

// Update: draw background
update_status ModuleCongrats::Update()
{
	bool end = false;

	// Draw everything --------------------------------------
	App->render->Blit(backgroundcongrats, 0, 0, &congratsrect, 0.75f); // back background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->congrats, App->menu);

	return UPDATE_CONTINUE;
}


bool ModuleCongrats::CleanUp()
{
	App->textures->Unload(backgroundcongrats);

	LOG("Unloading background scene");

	return true;
}