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
	backgroundrect.y = 512/2;
	backgroundrect.w = SCREEN_WIDTH;
	backgroundrect.h = 224;

	scoresrect.x = 0;
	scoresrect.y = 0;
	scoresrect.w = 256;
	scoresrect.h = 256;

}

ModuleScores::~ModuleScores()
{}

// Load assets
bool ModuleScores::Start()
{
	LOG("Loading scores assets");

	bool ret = true;
	backgroundscores = App->textures->Load("assets/sprites/GameOverScreen_Sprite.png");
	scoresranking = App->textures->Load("assets/sprites/Highscore_Sprite.png");
	scores_Sound = App->audio->LoadMusic("assets/music/17. Flower Dancing (Ranking).ogg");

	App->audio->PlayMusic(scores_Sound, ONCE);

	return ret;
}


// Update: draw background
update_status ModuleScores::Update()
{
	bool end = false;

	// Draw everything --------------------------------------
	App->render->Blit(backgroundscores, 0, 0, &backgroundrect); 
	App->render->Blit(scoresranking, 50, 20, &scoresrect);

	if (App->input->keyboard[SDL_SCANCODE_F] == 1)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(App->scores, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}


bool ModuleScores::CleanUp()
{
	App->textures->Unload(backgroundscores);
	App->audio->UnloadMusic(scores_Sound);

	LOG("Unloading background scene");

	return true;
}