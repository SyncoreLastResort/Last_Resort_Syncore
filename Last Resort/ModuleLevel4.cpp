#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleLevel4.h"
#include "ModuleEnemies.h"
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
	backgroundtilemaprect.x = 0;
	backgroundtilemaprect.y = 0;
	backgroundtilemaprect.w = 2699;
	backgroundtilemaprect.h = 224;


	//Wall mov down
	wallrect.x = 0;
	wallrect.y = 0;
	wallrect.w = 32;
	wallrect.h = 157;
	
	wallmovdownposition.x = 400;
	wallmovdownposition.y = -157;

	//Pinchy Wall
	pinchywallposition.x = 600;
	pinchywallposition.y = SCREEN_HEIGHT;

	pinchywalanim.PushBack({ 0, 0, 32, 177 });
	pinchywalanim.PushBack({ 32, 0, 32, 177 });
	pinchywalanim.PushBack({ 64, 0, 32, 177 });
	pinchywalanim.PushBack({ 96, 0, 30, 177 });
	pinchywalanim.speed = 0.15f;
	pinchywalanim.loop = true;

}

ModuleLevel4::~ModuleLevel4()
{}

// Load assets
bool ModuleLevel4::Start()
{
	LOG("Loading level1 scene");

	backgroundtilemap = App->textures->Load("assets/sprites/Stage4_tilemap.png");
	wall = App->textures->Load("assets/sprites/movingwall.png");
	pinchywall = App->textures->Load("assets/sprites/lastrespinchywall.png");

	
	boss_fight = false;

	start_time = SDL_GetTicks();


	//Music load
	main_track_lvl4 = App->audio->LoadMusic("assets/music/9. Melting point (stage 4).ogg");
	boss_track_lvl4 = App->audio->LoadMusic("assets/music/10. Dusky (Boss 4).ogg");

	App->player->p1dead = false;
	App->player2->p2dead = false;
	App->player2->life = 1;

	App->player->Enable();
	App->enemies->Enable();


	// Enemies ---
	
	colliderwallmovdown = App->collision->AddCollider({ wallmovdownposition.x, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
	colliderpinchywall = App->collision->AddCollider({ pinchywallposition.x, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);
		

	/*App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 200, 50);*/


	return true;
}

// UnLoad assets
bool ModuleLevel4::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(backgroundtilemap);
	App->textures->Unload(wall);
	App->textures->Unload(pinchywall);

	App->audio->UnloadMusic(main_track_lvl4);
	App->audio->UnloadMusic(boss_track_lvl4);

	App->player->Disable();
	App->enemies->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel4::Update()
{
	if (!boss_fight)
		App->audio->PlayMusic(main_track_lvl4,ONCE);
	
	if (boss_fight)
		App->audio->PlayMusic(boss_track_lvl4,ONCE);
	
	if (SDL_GetTicks() - start_time >= 202000 && !boss_fight) //After 202 seconds, the music changes from the maintrack to the boss track
	{
		App->audio->StopAudio();
		boss_fight = true;
	}

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

	
	//Wall movement
	if (maxreached == false && wallmovdownposition.y <= 0)
	{
		wallmovdownposition.y += 1;
		

	App->player->position.x += 1;
	App->player2->position.x += 1;
	

		if (wallmovdownposition.y == 0)
			maxreached = true;
	}
	if (maxreached == true && wallmovdownposition.y >= -157)
	{
		wallmovdownposition.y -= 1;
		

		if (wallmovdownposition.y == -157)
			maxreached = false;
	}
	colliderwallmovdown->SetPos(wallmovdownposition.x, wallmovdownposition.y);
	//End of Wall movement

	//Pinchy Walll movement

	if (maxreachedpinchy == false && pinchywallposition.y+177 >= SCREEN_HEIGHT)
	{
		pinchywallposition.y -= 1;


		if (pinchywallposition.y+177 == SCREEN_HEIGHT)
			maxreachedpinchy = true;
	}
	if (maxreachedpinchy == true && pinchywallposition.y <= SCREEN_HEIGHT)
	{
		pinchywallposition.y += 1;


		if (pinchywallposition.y == SCREEN_HEIGHT)
			maxreachedpinchy = false;
	}

	colliderpinchywall->SetPos(pinchywallposition.x, pinchywallposition.y);
	//End of Pinchy Wall movement
	

	
	App->render->Blit(backgroundtilemap, 0, 0, &backgroundtilemaprect, 1); // back background
	App->render->Blit(wall, wallmovdownposition.x, wallmovdownposition.y, &wallrect, 1);
	App->render->Blit(pinchywall, pinchywallposition.x, pinchywallposition.y, &pinchywalanim.GetCurrentFrame());
	// Draw everything --------------------------------------




	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN)
	{
		if (App->player2->life != 0)
		{
			App->player2->Enable();
			App->player2->life -= 1;
		}
	}

	return UPDATE_CONTINUE;
}