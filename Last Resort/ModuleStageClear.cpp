#include "ModuleStageClear.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h" 
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

ModuleStageClear::ModuleStageClear() {

	//StageClearImage
	graphicsrect.x = 0;
	graphicsrect.y = 32;
	graphicsrect.w = 212;
	graphicsrect.h = 16;
}

ModuleStageClear::~ModuleStageClear() {}

bool ModuleStageClear::Start() {

	LOG("Loading Stage Clear module");


	graphics = App->textures->Load("assets/sprites/All_Stage_Clears.png");
	stageclear_Sound = App->audio->LoadMusic("assets/audio/Stage_Clear.ogg");

	App->audio->PlayMusic(stageclear_Sound, ONCE);
	return true;
}

bool ModuleStageClear::CleanUp() {

	LOG("Unloading Stage Clear images");
	App->textures->Unload(graphics);
	App->audio->UnloadMusic(stageclear_Sound);
	return true;
}

update_status ModuleStageClear::Update() {

	//Draw everything
	App->render->Blit(graphics, 220, (SCREEN_HEIGHT / 2) - 8, &graphicsrect, 0.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE]) {
		App->fade->FadeToBlack(App->stageclear, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}