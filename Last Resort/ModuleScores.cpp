#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleScores.h"


ModuleScores::ModuleScores()
{
	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = 304;
	backgroundrect.h = 224;

}

ModuleScores::~ModuleScores()
{}

// Load assets
bool ModuleScores::Start()
{
	LOG("Loading scores assets");

	bool ret = true;
	backgroundscores = App->textures->Load("assets/sprites/GameOverScreen_Sprite.png");


	return ret;
}


// Update: draw background
update_status ModuleScores::Update()
{
	bool end = false;

	// Draw everything --------------------------------------
	App->render->Blit(backgroundscores, 0, 0, &backgroundrect); // back background

	if (App->input->keyboard[SDL_SCANCODE_F] == 1)
		App->fade->FadeToBlack(App->scores, App->scene_intro);

	return UPDATE_CONTINUE;
}


bool ModuleScores::CleanUp()
{
	App->textures->Unload(backgroundscores);

	LOG("Unloading background scene");

	return true;
}