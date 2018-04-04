#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"


ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	menuplace.x = 0;
	menuplace.y = 0;
	menuplace.w = 320;
	menuplace.h = 224;
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

// Load assets
bool ModuleWelcomeScreen::Start()
{
	bool ret = true;
	LOG("Loading welcome screen assets");

	Menu=App->textures->Load("assets/sprites/lastresortgametitle.png");
	
	if (IsEnabled() == true)
	{
		App->player->Disable();
	}

	return ret;
}




// Update: draw background
update_status ModuleWelcomeScreen::Update()
{
	bool end = false;

	// Draw everything --------------------------------------
	App->render->Blit(Menu, 0, 0, &menuplace); // bossimg background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(App->menu, App->background);

	return UPDATE_CONTINUE;
}

bool ModuleWelcomeScreen::CleanUp()
{
	// TODO 5: Remove all memory leaks
	App->textures->Unload(Menu);
	LOG("Unloading welcome screen stage");

	return true;
}