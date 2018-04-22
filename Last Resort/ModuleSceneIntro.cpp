#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleFirstBoss.h"
#include "ModuleBall.h"


ModuleSceneIntro::ModuleSceneIntro()
{
	introrect.x = 0;
	introrect.y = 0;
	introrect.w = 320;
	introrect.h = 224;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading intro");
	
	introbackground = App->textures->Load("assets/sprites/Last_Resort_Intro.png");
	maintrackintro = App->audio->LoadMusic("assets/music/1.Last resort title.ogg");
	
	App->render->camera.x = App->render->camera.y = 0;
	
	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(introbackground);
	/*App->audio->StopAudio();*/
	App->audio->UnloadMusic(maintrackintro);
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->audio->PlayMusic(maintrackintro, ONCE);
	// Draw everything --------------------------------------
	App->render->Blit(introbackground, 0, 0, &introrect);

	if(App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN && App->fade->IsFading() == false)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, (Module*)App->level1); 
		App->audio->StopAudio();
	}

	return UPDATE_CONTINUE;
}