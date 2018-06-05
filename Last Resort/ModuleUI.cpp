#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleLevel4.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"

#include <iostream>
#include <string.h>
#include <cstdio>

ModuleUI::ModuleUI() : Module() {}

ModuleUI::~ModuleUI() {}

bool ModuleUI::Start() {

	UI_Main_Menu = App->textures->Load("assets/sprites/All_Stage_Clears.png");

	//fonts
	font = App->fonts->Load("assets/fonts/Font_score.png", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_.,[]&$ ", 2);
	Insert_Coin = App->audio->LoadSoundEffect("assets/sounds/Insert_Coin.wav");

	UI_ship.x = 0; //UI_Ship
	UI_ship.y = 9;
	UI_ship.w = 16;
	UI_ship.h = 8;


	UI_ship2.x = 168;
	UI_ship2.y = 25;
	UI_ship2.w = 17;
	UI_ship2.h = 6;

	coins = 0;
	return true;
}


bool ModuleUI::CleanUp() {

	App->audio->UnloadSoundEffect(Insert_Coin);
	App->textures->Unload(UI_Main_Menu);
	App->fonts->UnLoad(font);
	

	return true;
}

update_status ModuleUI::Update() {

	P1Life = App->player->life;
	P2Life = App->player2->life;

	if (App->scene_intro->IsEnabled() == true)
	{
		if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN && coins < 100) {
			coins++;
			Mix_PlayChannel(-1, Insert_Coin, 0);
		}


		sprintf_s(coins_text, "%7d", coins);
		App->fonts->BlitText((SCREEN_WIDTH - 104), (SCREEN_HEIGHT - 10), font, "CREDITS");
		App->fonts->BlitText((SCREEN_WIDTH - 75), (SCREEN_HEIGHT - 10), font, coins_text);
	}

	
	if (App->level4->IsEnabled())
	{
		sprintf_s(life_text, "%7d", P1Life);
		sprintf_s(life2_text, "%7d", P2Life);

		App->fonts->BlitText(30, 24, font, "X");
		App->fonts->BlitText(13, 16, font, "P1");
		/*App->fonts->BlitText(13, 11, font, "_");
		App->fonts->BlitText(29, 15, font, "_");*/

		App->render->Blit(UI_Main_Menu, 13, 24, &UI_ship, 0.0f, false); 

		App->fonts->BlitText(-2, 24, font, life_text);


		App->fonts->BlitText((SCREEN_WIDTH - 75), 24, font, "X");
		App->fonts->BlitText((SCREEN_WIDTH - 107), 24, font, life2_text);

		App->fonts->BlitText((SCREEN_WIDTH - 92), 16, font, "P2");
		/*App->fonts->BlitText((SCREEN_WIDTH - 76), 15, font, "_");
		App->fonts->BlitText((SCREEN_WIDTH - 76), 11, font, "_");*/

		App->render->Blit(UI_Main_Menu, (SCREEN_WIDTH - 92), 24, &UI_ship2, 0.0f, false);
	}

	////TOP Score
	//if (App->scene1background->IsEnabled() == true) {

	//	uint MaxScore = ScoreP1 + ScoreP2;

	//	if (MaxScore > TopScore)
	//		TopScore = MaxScore;
	//}

		/*sprintf_s(top_score, "%7d", TopScore);

		BlitText((SCREEN_WIDTH / 2) - 41, 16, font, "T0P");
		BlitText((SCREEN_WIDTH / 2) - 9, 16, font, top_score);*/


		//GOD MODE

		if (App->player->godmode) {

			App->fonts->BlitText(13, SCREEN_HEIGHT - 10, font, "GOD");
			App->fonts->BlitText(39, SCREEN_HEIGHT - 10, font, "MODE");
		}


		return UPDATE_CONTINUE;
	}



