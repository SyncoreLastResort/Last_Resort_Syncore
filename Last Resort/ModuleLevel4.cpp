#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleLevel4.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"


ModuleLevel4::ModuleLevel4()
{
	//Background 
//	backgroundtilemaprect.x = 0;
//	backgroundtilemaprect.y = 0;
//	backgroundtilemaprect.w = 2699;
//	backgroundtilemaprect.h = 224;

	//Background
	backgroundtilemaprect.x = 0;
	backgroundtilemaprect.y = 0;
	backgroundtilemaprect.w = 4143;
	backgroundtilemaprect.h = 219;

	//Foreground
	foregroundtilemaprect.x = 0;
	foregroundtilemaprect.y = 0;
	foregroundtilemaprect.w = 4143;
	foregroundtilemaprect.h = 222;

	//cannon platform
	cannon_platform.x = 161;
	cannon_platform.y = 130;
	cannon_platform.w = 79;
	cannon_platform.h = 26;

	cannon_platform_end.x = 0;
	cannon_platform_end.y = 0;
	cannon_platform_end.w = 79;
	cannon_platform_end.h = 49;

	//Background lava animations
	Back_Lava.PushBack({ 0,0,2493,219 });
	Back_Lava.PushBack({ 0,224,2493,219 });	
	Back_Lava.PushBack({ 0,224,2493,219 });
	Back_Lava.PushBack({ 0,0,2493,219 });
	
	op_cannon.PushBack({ 161,130,79,26 });
	op_cannon.PushBack({ 81,129,79,27 });
	op_cannon.PushBack({ 0,128,79,29 });
	op_cannon.PushBack({ 160,94,79,31 });
	op_cannon.PushBack({ 80,93,79,33 });
	op_cannon.PushBack({ 0,92,79,35 });
	op_cannon.PushBack({ 160,52,79,37 });
	op_cannon.PushBack({ 80,51,79,39 });
	op_cannon.PushBack({ 0,50,79,41 });
	op_cannon.PushBack({ 160,3,79,43 });
	op_cannon.PushBack({ 80,2,79,45 });
	op_cannon.PushBack({ 0,0,79,49 });
	op_cannon.Finished();
	
}

ModuleLevel4::~ModuleLevel4()
{}

// Load assets
bool ModuleLevel4::Start()
{
	LOG("Loading level1 scene");

//	backgroundtilemap = App->textures->Load("assets/sprites/Stage4_tilemap.png");
	backgroundtilemap = App->textures->Load("assets/sprites/Background.png");
	foregroundtilemap = App->textures->Load("assets/sprites/Foreground.png");
	BackLavaAnim = App->textures->Load("assets/sprites/Back_Lava_Anim.png");
	Enemies_1 = App->textures->Load("assets/sprites/Enemys_Stage4_Sprites.png");

	App->player->p1dead = false;
	App->player2->p2dead = false;
	App->player2->life = 1;

	App->player->Enable();


	return true;
}

// UnLoad assets
bool ModuleLevel4::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(backgroundtilemap);

	App->player->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel4::Update()
{
	// Move camera forward -----------------------------
	App->render->camera.x += 1 * SCREEN_SIZE;
	


	if (App->player->IsEnabled() == false && App->player2->IsEnabled() == false)
	{
		App->fade->FadeToBlack(this, App->gameover);
	}

	if (App->player2->IsEnabled() == true && App->player->p1dead == true)
	{
		App->player->current_animation = &App->player->death;
		if (App->player->current_animation->Finished() == true)
			App->player->Disable();
	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, App->stageclear);
	}

	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, App->gameover);
	}


	App->player->position.x += 1;

	// Draw everything --------------------------------------

	App->render->Blit(backgroundtilemap, 0, 0, &backgroundtilemaprect, 0.75); // back background
	App->render->Blit(BackLavaAnim, 0, 0, &Back_Lava.GetCurrentFrame(), 0.75);
	App->render->Blit(foregroundtilemap, 0, 0, &foregroundtilemaprect, 0.75); // back background
//	App->render->Blit(Enemies_1, 400, 100, &cannon_platform, 0.75);
	if (op_cannon.Finished() != true) {
		App->render->Blit(Enemies_1, 400, 100, &op_cannon.GetCurrentFrame(), 0.75);
	}
	else {
		App->render->Blit(Enemies_1, 400, 100, &cannon_platform_end, 0.75);
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == 1)
	{
		if (App->player2->life != 0)
		{
			App->player2->Enable();
			App->player2->life -= 1;
		}
	}

	return UPDATE_CONTINUE;
}