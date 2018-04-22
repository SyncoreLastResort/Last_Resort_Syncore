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
#include "ModuleFonts.h"


#include<stdio.h>


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
	font_scorenums = App->fonts->Load("assets/fonts/Font_red.png", "0123456789", 1);

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

	// Draw UI (score) --------------------------------------
	if (App->player->score > App->player->score2)
	{
		sprintf_s(score_text, 10, "%7d", App->player->score);
		sprintf_s(score_text2, 10, "%7d", App->player->score2);


		// TODO 3: Blit the text of the score in at the bottom of the screen
		App->fonts->BlitText(120, 52, font_scorenums, score_text);
		App->fonts->BlitText(120, 66, font_scorenums, score_text2);
		App->fonts->BlitText(SCREEN_WIDTH - 122, 52, App->player->font_score, "PLAYER1");
		App->fonts->BlitText(SCREEN_WIDTH - 122, 66, App->player->font_score, "PLAYER2");
	}

	else
	{
		sprintf_s(score_text, 10, "%7d", App->player->score);
		sprintf_s(score_text2, 10, "%7d", App->player->score2);


		// TODO 3: Blit the text of the score in at the bottom of the screen
		App->fonts->BlitText(120, 66, font_scorenums, score_text);
		App->fonts->BlitText(120, 52, font_scorenums, score_text2);
		App->fonts->BlitText(SCREEN_WIDTH - 122, 66, App->player->font_score, "PLAYER1");
		App->fonts->BlitText(SCREEN_WIDTH - 122, 52, App->player->font_score, "PLAYER2");


	}

	return UPDATE_CONTINUE;
}


bool ModuleScores::CleanUp()
{
	App->textures->Unload(backgroundscores);
	App->textures->Unload(scoresranking);
	App->audio->UnloadMusic(scores_Sound);
	App->fonts->UnLoad(font_scorenums);
	App->fonts->UnLoad(App->player->font_score);

	LOG("Unloading background scene");

	return true;
}