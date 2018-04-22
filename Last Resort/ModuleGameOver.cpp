#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleGameOver.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleLevel1.h"



ModuleGameOver::ModuleGameOver()
{
	background.x = 0;
	background.y = 0;
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
}


ModuleGameOver::~ModuleGameOver()
{
}

bool ModuleGameOver::Start() {

	LOG("Loading gameover module");
	graphics = App->textures->Load("assets/sprites/GameOver.png");
	gameover_Sound = App->audio->LoadMusic("assets/music/GameOver.ogg");

	App->audio->PlayMusic(gameover_Sound,ONCE);

	return true;
}

bool ModuleGameOver::CleanUp() {

	LOG("Unloading gameober module");
	App->textures->Unload(graphics);
	App->audio->UnloadMusic(gameover_Sound);

	return true;
}

update_status ModuleGameOver::Update() {

	App->render->Blit(graphics, 0, 0, &background, 0);

	if (App->input->keyboard[SDL_SCANCODE_SPACE]) {
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(App->gameover, App->scene_intro);
		App->audio->StopAudio();
	}

	return UPDATE_CONTINUE;
}