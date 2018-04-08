#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleIntroScene.h"
#include "ModuleLevel1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleIntroScene::ModuleIntroScene()
{
	introrect.x = 0;
	introrect.y = 0;
	introrect.w = 320;
	introrect.h = 224;
}

ModuleIntroScene::~ModuleIntroScene()
{}

// Load assets
bool ModuleIntroScene::Start()
{
	LOG("Loading space scene");

	introbackground = App->textures->Load("assets/sprites/lastresortgametitle.png");
	maintrackintro = App->audio->LoadMusic("assets/sounds/1.Last resort title.ogg");
	App->level1->Disable();
	App->player->Disable();

	return true;
}

// UnLoad assets
bool ModuleIntroScene::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(introbackground);
	App->audio->StopAudio();
	App->audio->UnloadMusic(maintrackintro);
	return true;
}

// Update: draw background
update_status ModuleIntroScene::Update()
{
	// Move camera forward -----------------------------
	//int scroll_speed = 1;

	////App->player->position.x += 1;
	//App->render->camera.x -= 3;

	App->audio->PlayMusic(maintrackintro, ONCE);
	// Draw everything --------------------------------------
	App->render->Blit(introbackground, 0, 0, &introrect);
	if(App->input->keyboard[SDL_SCANCODE_SPACE]==1)
	App->fade->FadeToBlack(this, App->level1);
	return UPDATE_CONTINUE;
}