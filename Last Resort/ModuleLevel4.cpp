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
	

	backgroundtilemaprect.w = 2699;
	backgroundtilemaprect.h = 224;

	//Background 
	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = 4143;
	backgroundrect.h = 224;

	//Foreground
	foregroundrect.x = 0;
	foregroundrect.y = 0;
	foregroundrect.w = 4143;
	foregroundrect.h = 224;

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

//	backgroundtilemap = App->textures->Load("assets/sprites/Stage4_tilemap.png");
	backgroundtilemap = App->textures->Load("assets/sprites/Background.png");
	foregroundtilemap = App->textures->Load("assets/sprites/Foreground.png");
	BackLavaAnim = App->textures->Load("assets/sprites/Back_Lava_Anim.png");
	Enemies_1 = App->textures->Load("assets/sprites/Enemys_Stage4_Sprites.png");
	backgroundtilemap = App->textures->Load("assets/sprites/Stage4_tilemap.png");
	background = App->textures->Load("assets/sprites/Background.png");
	foreground = App->textures->Load("assets/sprites/Foreground.png");

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
		

	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 300, SCREEN_HEIGHT-65);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 500, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 550, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 600, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 650, SCREEN_HEIGHT / 2);


	return true;
}

// UnLoad assets
bool ModuleLevel4::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(backgroundtilemap);
	App->textures->Unload(wall);
	App->textures->Unload(pinchywall);
	App->textures->Unload(background);
	App->textures->Unload(foreground);

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


	// Move camera forward -----------------------------
	App->render->camera.x += 1 * SCREEN_SIZE;

	App->player->position.x += 1;

	if (App->player2->IsEnabled() == true)
		App->player2->position.x += 1;

	if (!boss_fight)
		App->audio->PlayMusic(main_track_lvl4,ONCE);
	
	if (boss_fight)
		App->audio->PlayMusic(boss_track_lvl4,ONCE);
	
	if (SDL_GetTicks() - start_time >= 202000 && !boss_fight) //After 202 seconds, the music changes from the maintrack to the boss track
	{
		App->audio->StopAudio();
		boss_fight = true;
	}
	
	

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
	}

	/*App->player->position.x += 1;*/
	App->player2->position.x += 1;

		if (wallmovdownposition.y == 0)
		{	
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
	

	App->render->Blit(background, 0, 0, &backgroundrect, 1); //background
	//App->render->Blit(backgroundtilemap, 0, 0, &backgroundtilemaprect, 1); // back background
	App->render->Blit(wall, wallmovdownposition.x, wallmovdownposition.y, &wallrect, 1);
	App->render->Blit(pinchywall, pinchywallposition.x, pinchywallposition.y, &pinchywalanim.GetCurrentFrame());
	App->render->Blit(foreground, 0, 0, &foregroundrect, 1); //foreground
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