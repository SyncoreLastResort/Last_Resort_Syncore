#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnemies.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "SDL\include\SDL_render.h"
#include "ModuleFirstBoss.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

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
	bossplace.w = 304;
	bossplace.h = 224;

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

	
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading level1 scene");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->boss1->Enable();

	hud = App->textures->Load("rtype/hud.png");
	background_lights = App->textures->Load("assets/sprites/Lasers_Sprite.png");
	backbackground = App->textures->Load("assets/sprites/BackBackground_Sprite.png");
	midbackground = App->textures->Load("assets/sprites/MidBackground_Sprite.png");
	road = App->textures->Load("assets/sprites/Road&Tunnel_Background.png");
	bossimg = App->textures->Load("assets/sprites/Boss_Static_Background.png");
	maintracklvl1 = App->audio->LoadMusic("assets/music/2. Jack to the metro (Stage 1).ogg");
	
	// Enemies ---

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 400, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 432, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 464, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 498, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 632, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 664, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 698, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 800, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 832, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 864, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::WASP, 898, 120);

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
	
	
	
	App->audio->StopAudio();
	App->audio->UnloadMusic(maintracklvl1);

	App->enemies->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->boss1->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{
	// Move camera forward -----------------------------
	/*App->render->camera.x += 1 * SCREEN_SIZE;*/

	if (App->input->keyboard[SDL_SCANCODE_F] == 1)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(App->level1, App->level2);
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

	App->render->Blit(hud, 0, 240, NULL, 0.0f, false);
	
	
	

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