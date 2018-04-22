#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleLevel1.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFirstBoss.h"
#include "ModuleBall.h"


ModuleLevel1::ModuleLevel1()
{
	// ground (road & tunnel)
	ground.x = 0;
	ground.y = 0;
	ground.w = 4408;
	ground.h = 239;

	// BackBackground 
	background.x = 0;
	background.y = 0;
	background.w = 803;
	background.h = 160;

	//midback
	midback.x = 0;
	midback.y = 0;
	midback.w = 1303;
	midback.h = 160;

	//bossplace
	bossplace.x = 0;
	bossplace.y = 0;
	bossplace.w = SCREEN_WIDTH;
	bossplace.h = SCREEN_HEIGHT;

	//Power up place
	/*powerupplace.x=*/

	thick_lights.PushBack({ 133,2,25,144 });
	thick_lights.PushBack({ 158,2,38,144 }); // From left to right
	thick_lights.PushBack({ 196,2,52,144 }); // From left to right
	thick_lights.PushBack({ 248,2,65,144 }); // From left to right
	thick_lights.PushBack({ 313,2,81,144 }); // From left to right
	thick_lights.PushBack({ 394,2,98,144 }); // From left to right
	thick_lights.PushBack({ 17,159,121,144 }); // From left to right
	thick_lights.PushBack({ 138,159,143,144 }); // Limit   -   now I copy the same pushbacks in reverse order
	thick_lights.PushBack({ 17,159,121,144 }); //From right to left
	thick_lights.PushBack({ 394,2,98,144 }); //From right to left
	thick_lights.PushBack({ 313,2,81,144 }); //From right to left
	thick_lights.PushBack({ 248,2,65,144 }); //From right to left
	thick_lights.PushBack({ 196,2,52,144 }); //From right to left
	thick_lights.PushBack({ 158,2,38,144 }); //From right to left
	thick_lights.speed = 0.15f;

	////Powe up animation
	//Power_Up.PushBack({ 18,64,31,16 });
	//Power_Up.PushBack({ 49,64,31,16 });
	//Power_Up.loop = true;
	//Power_Up.speed = 0.05f;

	
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading level1 scene");

	App->player->Enable();
	App->enemies->Enable();
	App->boss1->Enable();

	scroll_lights = 0;
	scrollground = 0;
	scrollmid = 0;
	scrollback = 0;

	background_lights = App->textures->Load("assets/sprites/Lasers_Sprite.png");
	backbackground = App->textures->Load("assets/sprites/BackBackground_Sprite.png");
	midbackground = App->textures->Load("assets/sprites/MidBackground_Sprite.png");
	road = App->textures->Load("assets/sprites/Road&Tunnel_Background.png");
	bossimg = App->textures->Load("assets/sprites/Boss_Static_Background.png");
	maintracklvl1 = App->audio->LoadMusic("assets/music/2. Jack to the metro (Stage 1).ogg");
	/*powerups = App->textures->Load("assets/sprites/PowerUps_Sprite.png");*/
	

	// Enemies ---

	App->enemies->AddEnemy(ENEMY_TYPES::POWER_UP, 100, 50);

	//Wasp Wave 1

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 400, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 450, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 500, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 550, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 750, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 800, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 850, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 900, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 1000, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 1050, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 1100, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 1150, 80);


	//Rhino Wave 1
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 850, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 950, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 1050, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 1150, 75);

	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 1350, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 1450, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 1550, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 1650, 75);


	//Wasp Wave 2
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 2850, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 2900, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 2950, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3000, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3050, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3100, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3150, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3200, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3250, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3300, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3350, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3400, 80);


	//Rhino Wave 2
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3000, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3100, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3200, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3300, 75);

	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3600, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3700, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3800, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 3900, 75);

	//Wasp wave 3

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3800, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3850, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3900, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 3950, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4100, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4150, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4200, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4250, 160);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4400, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4450, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4500, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 4550, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 5200, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 5250, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 5300, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 5350, 160);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 6400, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 6450, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 6500, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 6550, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 7200, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 7250, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 7300, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 7350, 160);

	
	//Rhino Wave 2
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4200, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4300, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4400, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4500, 75);

	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4800, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4900, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 5000, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 5100, 75);

	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 6200, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 6300, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 6400, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 6500, 75);

	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 6800, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 6900, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 7000, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 7100, 75);

	

	return true;
}

// UnLoad assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(backbackground);
	App->textures->Unload(background_lights);
	App->textures->Unload(midbackground);
	App->textures->Unload(road);
	App->textures->Unload(bossimg);
	//App->textures->Unload(powerups);
	
	
	App->audio->StopAudio();
	App->audio->UnloadMusic(maintracklvl1);

	if(App->boss1->IsEnabled())
	App->boss1->Disable();

	App->enemies->Disable();

	App->player->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Move camera forward -----------------------------
	/*App->render->camera.x += 1 * SCREEN_SIZE;*/
	/*if (ground.x == -ground.w)
		App->boss1->Enable();*/

	// Utility conditions, used to move forward or backwards at high speed
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_REPEAT)
	{
		scroll_lights -= 2.5;
		scrollground -= 5.5;
		scrollmid -= 2.5;
		scrollback -= 1.5;
	}
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_REPEAT)
	{
		scroll_lights += 2.5;
		scrollground += 5.5;
		scrollmid += 2.5;
		scrollback += 1.5;
	}

	if (App->input->keyboard[SDL_SCANCODE_F] == 1)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(App->level1, App->stageclear);
	}

	if (App->input->keyboard[SDL_SCANCODE_F] == 1)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(App->level1, App->stageclear);
	}
	
	/*App->player->position.x += 1;
	App->render->camera.x -= 3;
	*/

	// Draw everything --------------------------------------
	App->render->Blit(bossimg, 0, 0, &bossplace); // bossimg background
	App->render->Blit(backbackground, scrollback, 0, &background, 0.75f); // back background
	App->render->Blit(background_lights, scroll_lights, -2, &thick_lights.GetCurrentFrame(), 0.75f);
	App->render->Blit(midbackground, scrollmid, 32, &midback, 0.75f); // mid background
	App->render->Blit(road, scrollground, 0, &ground); //road & tunnel

	/*App->render->Blit(powerups, 0, 0, &powerupplace);*/

	
	App->audio->PlayMusic(maintracklvl1, ONCE);

	scroll_lights -= 0.25;
	scrollground -= 0.55;
	scrollmid -= 0.25;
	scrollback -= 0.15;


	if (App->input->keyboard[SDL_SCANCODE_2] == 1)
	{
		App->player2->Enable();
	}
	
	return UPDATE_CONTINUE;
}