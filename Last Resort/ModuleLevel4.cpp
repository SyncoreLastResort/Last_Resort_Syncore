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
#include "ModuleBoss4.h"
#include "ModuleUI.h"
#include "ModuleScores.h"



ModuleLevel4::ModuleLevel4()
{
	////Background 
	//backgroundtilemaprect.x = 0;
	//backgroundtilemaprect.y = 0;
	//backgroundtilemaprect.w = 2699;
	//backgroundtilemaprect.h = 224;

	////Background 
	//backgroundrect.x = 0;
	//backgroundrect.y = 0;
	//backgroundrect.w = 4143;
	//backgroundrect.h = 224;

	////Foreground
	//foregroundrect.x = 0;
	//foregroundrect.y = 0;
	//foregroundrect.w = 4143;
	//foregroundrect.h = 224;

	//Background
	backgroundtilemaprect.x = 0;
	backgroundtilemaprect.y = 0;
	backgroundtilemaprect.w = 2862;
	backgroundtilemaprect.h = SCREEN_HEIGHT;

	//Foreground
	foregroundtilemaprect1.x = 0;
	foregroundtilemaprect1.y = 0;
	foregroundtilemaprect1.w = 2734;
	foregroundtilemaprect1.h = SCREEN_HEIGHT;

	foregroundtilemaprect2.x = 0;
	foregroundtilemaprect2.y = 0;
	foregroundtilemaprect2.w = 1271;
	foregroundtilemaprect2.h = SCREEN_HEIGHT;

	//up & down platforms and animations
	foreground_platforms.x = 46;
	foreground_platforms.y = 67;
	foreground_platforms.w = 63;
	foreground_platforms.h = 8;

	platform_up.PushBack({ 46,67,63,8 });
	platform_up.PushBack({ 9,46,63,7 });
	platform_up.PushBack({ 9,85,63,7 });
	platform_up.PushBack({ 9,46,63,7 });
	platform_up.PushBack({ 46,67,63,8 });

	platform_down.PushBack({ 46,67,63,8 });
	platform_down.PushBack({ 82,47,63,7 });
	platform_down.PushBack({ 82,85,63,7 });
	platform_down.PushBack({ 82,47,63,7 });
	platform_down.PushBack({ 46,67,63,8 });

	//Background lava animations
	Back_Lava.PushBack({ 0,0,1216,219 });
	Back_Lava.PushBack({ 0,224,1216,219 });
	Back_Lava.PushBack({ 0,224,1216,219 });
	Back_Lava.PushBack({ 0,0,1216,219 });
	Back_Lava.speed = 0.05f;

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

	op_cannon.PushBack({ 80,2,79,45 });
	op_cannon.PushBack({ 160,3,79,43 });
	op_cannon.PushBack({ 0,50,79,41 });
	op_cannon.PushBack({ 80,51,79,39 });
	op_cannon.PushBack({ 160,52,79,37 });
	op_cannon.PushBack({ 0,92,79,35 });
	op_cannon.PushBack({ 80,93,79,33 });
	op_cannon.PushBack({ 160,94,79,31 });
	op_cannon.PushBack({ 0,128,79,29 });
	op_cannon.PushBack({ 81,129,79,27 });
	op_cannon.PushBack({ 161,130,79,26 });

	op_cannon.speed = 0.15f;

	//Wall mov down
	wallrect.x = 0;
	wallrect.y = 0;
	wallrect.w = 32;
	wallrect.h = 157;
	
	wallmovdownposition.x = 600;
	wallmovdownposition.y = -200;

	wallmovdownposition2.x = 600;
	wallmovdownposition2.y = -200;

	wallmovdownposition3.x = 600;
	wallmovdownposition3.y = -200;

	wallmovdownposition4.x = 600;
	wallmovdownposition4.y = -200;

	//Pinchy Wall
	pinchywallposition.x = 600;
	pinchywallposition.y = SCREEN_HEIGHT;

	pinchywallposition2.x = 600;
	pinchywallposition2.y = SCREEN_HEIGHT;

	pinchywallposition3.x = 600;
	pinchywallposition3.y = SCREEN_HEIGHT;

	pinchywallposition4.x = 600;
	pinchywallposition4.y = SCREEN_HEIGHT;

	pinchywalanim.PushBack({ 0, 0, 32, 177 });
	pinchywalanim.PushBack({ 32, 0, 32, 177 });
	pinchywalanim.PushBack({ 64, 0, 32, 177 });
	pinchywalanim.PushBack({ 96, 0, 30, 177 });
	pinchywalanim.speed = 0.075f;
	pinchywalanim.loop = true;

}

ModuleLevel4::~ModuleLevel4()
{}

// Load assets
bool ModuleLevel4::Start()
{
	LOG("Loading level1 scene");

	backgroundtilemap = App->textures->Load("assets/sprites/Background.png");
	foregroundtilemap1 = App->textures->Load("assets/sprites/foreground_1.png");
	foregroundtilemap2 = App->textures->Load("assets/sprites/foreground_2.png");
	foreground_platform = App->textures->Load("assets/sprites/foreground_3.png");
	BackLavaAnim = App->textures->Load("assets/sprites/Back_Lava_Anim.png");

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
	App->scores->Enable();

	//Background colliders
	

	// Enemies ---
	
	if (createcollidersonce == false)
	{
		foregroundcoll = App->collision->AddCollider({ foregroundtilemaprect1.x, foregroundtilemaprect1.y, foregroundtilemaprect1.w - 1125,35 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll2 = App->collision->AddCollider({ foregroundtilemaprect1.x, SCREEN_HEIGHT - 35, foregroundtilemaprect1.w - 1125,35 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll3 = App->collision->AddCollider({ foregroundtilemaprect1.w-1125, SCREEN_HEIGHT - 18, 1000, 18 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll4 = App->collision->AddCollider({ foregroundtilemaprect1.w - 1125, 0, 1000, 18 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll5 = App->collision->AddCollider({ foregroundtilemaprect1.w - 990, 0, 60, 36 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll5 = App->collision->AddCollider({ foregroundtilemaprect1.w - 990, SCREEN_HEIGHT-36, 60, 36 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll6 = App->collision->AddCollider({ foregroundtilemaprect1.w-380, foregroundtilemaprect1.y, 380, 35 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll7 = App->collision->AddCollider({ foregroundtilemaprect1.w-380, SCREEN_HEIGHT - 35, 380, 35 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll8 = App->collision->AddCollider({ 4100, SCREEN_HEIGHT - 35, 1300, 32 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll9 = App->collision->AddCollider({ 4100, 0, 1300, 32 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll10 = App->collision->AddCollider({ 5045, 0, 50, 95 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll11 = App->collision->AddCollider({ 5045, SCREEN_HEIGHT-98, 50, 100 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll12 = App->collision->AddCollider({ 5045, SCREEN_HEIGHT - 98, 65, 32 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll13 = App->collision->AddCollider({ 5045, 60, 65, 32 }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll14 = App->collision->AddCollider({ 5330, 0, 55, SCREEN_HEIGHT }, COLLIDER_TYPE::COLLIDER_WALL);
		foregroundcoll15 = App->collision->AddCollider({ foregroundtilemaprect1.w-685, 90, 240, 40 }, COLLIDER_TYPE::COLLIDER_WALL);

		colliderwallmovdown = App->collision->AddCollider({ wallmovdownposition.x+1500, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderpinchywall = App->collision->AddCollider({ pinchywallposition.x+1500, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);

		colliderwallmovdown2 = App->collision->AddCollider({ wallmovdownposition.x + 1600, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderpinchywall2 = App->collision->AddCollider({ pinchywallposition.x + 1600, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);

		colliderwallmovdown3 = App->collision->AddCollider({ wallmovdownposition.x + 1700, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderpinchywall3 = App->collision->AddCollider({ pinchywallposition.x + 1700, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);

		colliderwallmovdown4 = App->collision->AddCollider({ wallmovdownposition.x + 1800, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderpinchywall4 = App->collision->AddCollider({ pinchywallposition.x + 1800, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);

		colliderplatform1 = App->collision->AddCollider({ 875, SCREEN_HEIGHT/2 +10, 80, 30 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderplatform2 = App->collision->AddCollider({ 975, SCREEN_HEIGHT / 3 + 10, 80, 30 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderplatform3 = App->collision->AddCollider({ 1075, SCREEN_HEIGHT -100 + 10, 80, 30 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderplatform4 = App->collision->AddCollider({ 1175, SCREEN_HEIGHT / 4 + 10, 80, 30 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderplatform5 = App->collision->AddCollider({ 1420, SCREEN_HEIGHT / 2 + 10, 80, 30 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderplatform6 = App->collision->AddCollider({ 1500, SCREEN_HEIGHT / 4 + 10, 80, 30 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderplatform7 = App->collision->AddCollider({ 1580, SCREEN_HEIGHT / 3 + 20, 80, 30 }, COLLIDER_TYPE::COLLIDER_WALL);

	/*	colliderwallmovdown = App->collision->AddCollider({ wallmovdownposition.x, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderpinchywall = App->collision->AddCollider({ pinchywallposition.x, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);

		colliderwallmovdown = App->collision->AddCollider({ wallmovdownposition.x, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderpinchywall = App->collision->AddCollider({ pinchywallposition.x, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);

		colliderwallmovdown = App->collision->AddCollider({ wallmovdownposition.x, wallmovdownposition.y, 32, 157 }, COLLIDER_TYPE::COLLIDER_WALL);
		colliderpinchywall = App->collision->AddCollider({ pinchywallposition.x, pinchywallposition.y, 32, 177 }, COLLIDER_TYPE::COLLIDER_WALL);*/

		createcollidersonce = true;
	}


	App->enemies->AddEnemy(ENEMY_TYPES::POWER_UP, 500, SCREEN_HEIGHT / 3);
	App->enemies->AddEnemy(ENEMY_TYPES::POWER_UP_BOMB, 500, SCREEN_HEIGHT -75);

	App->enemies->AddEnemy(ENEMY_TYPES::POWER_UP, 2500, SCREEN_HEIGHT / 3);
	App->enemies->AddEnemy(ENEMY_TYPES::POWER_UP_BOMB, 2500, SCREEN_HEIGHT -75);


	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 300, SCREEN_HEIGHT-65);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 350, SCREEN_HEIGHT - 65);*/
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 400, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 450, SCREEN_HEIGHT / 6 - 5);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Spider, 500, SCREEN_HEIGHT - 65);*/
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 550, SCREEN_HEIGHT / 6 - 5);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 560, SCREEN_HEIGHT - 50);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 600, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 675, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 700, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 775, SCREEN_HEIGHT / 6 - 5);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Spider, 850, SCREEN_HEIGHT - 65);*/
	App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 875, SCREEN_HEIGHT /2);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Spider, 900, SCREEN_HEIGHT / 6 - 5);*/
	App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 975, SCREEN_HEIGHT / 3);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1000, SCREEN_HEIGHT / 6 - 5);
	//App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1000, SCREEN_HEIGHT / 6 - 5);
	App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 1075, SCREEN_HEIGHT - 100);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1100, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 1175, SCREEN_HEIGHT / 4);
	//App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1200, SCREEN_HEIGHT - 65);
	//App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1225, SCREEN_HEIGHT - 65);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1300, SCREEN_HEIGHT / 6 - 5);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1330, SCREEN_HEIGHT / 6 - 5);*/
	/*App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 1350, SCREEN_HEIGHT / 3);*/
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1400, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 1420, SCREEN_HEIGHT / 2);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1450, SCREEN_HEIGHT / 6 - 5);*/
	App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 1500, SCREEN_HEIGHT / 4);
	App->enemies->AddEnemy(ENEMY_TYPES::CannonPlatf, 1580, SCREEN_HEIGHT / 3 +10);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1600, SCREEN_HEIGHT - 65);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Spider, 1650, SCREEN_HEIGHT / 6 - 5);*/
	//App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 1700, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 1900, SCREEN_HEIGHT / 2 +50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 1930, SCREEN_HEIGHT / 2 +50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 1960, SCREEN_HEIGHT / 2 +50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 1990, SCREEN_HEIGHT / 2 +50);
	/*App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2020, SCREEN_HEIGHT / 2 +50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2050, SCREEN_HEIGHT / 2 +50);*/
	//App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 1950, SCREEN_HEIGHT - 65);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 1980, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2010, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2040, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2070, SCREEN_HEIGHT / 5);
	//App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2100, SCREEN_HEIGHT / 5);
	//App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2130, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 2350, SCREEN_HEIGHT - 50);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 2420, SCREEN_HEIGHT /2 + 5);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 2490, SCREEN_HEIGHT - 50);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 2530, SCREEN_HEIGHT - 50);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 2560, SCREEN_HEIGHT - 50);*/
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2600, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2630, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2660, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2690, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 2700, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 2800, SCREEN_HEIGHT / 6 - 10);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 2800, SCREEN_HEIGHT - 60);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2850, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2880, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2910, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 2940, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3100, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3150, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3200, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3250, SCREEN_HEIGHT / 2);
	/*App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3300, SCREEN_HEIGHT -20);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3350, SCREEN_HEIGHT -20);*/
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3400, SCREEN_HEIGHT -20);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3450, SCREEN_HEIGHT -20);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3500, SCREEN_HEIGHT -20);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3550, SCREEN_HEIGHT / 2);
	/*App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3600, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3650, SCREEN_HEIGHT / 2);*/
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3700, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3750, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3800, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3850, SCREEN_HEIGHT / 5);
	//App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3900, SCREEN_HEIGHT / 5);
	//App->enemies->AddEnemy(ENEMY_TYPES::TrackingBee, 3950, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4050, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4080, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4110, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4140, SCREEN_HEIGHT / 2 + 50);
	//App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4170, SCREEN_HEIGHT / 2 + 50);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4150, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4180, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4210, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4240, SCREEN_HEIGHT / 5);
	//App->enemies->AddEnemy(ENEMY_TYPES::RedBird, 4270, SCREEN_HEIGHT / 5);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 4350, SCREEN_HEIGHT / 6 - 10);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 4350, SCREEN_HEIGHT - 60);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 4400, SCREEN_HEIGHT / 6 - 10);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 4400, SCREEN_HEIGHT - 60);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 4500, SCREEN_HEIGHT / 4);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 4550, SCREEN_HEIGHT / 3);*/
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4600, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4650, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4700, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4750, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::Power_Up_Holder, 4800, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::RHINO, 4850, SCREEN_HEIGHT / 2);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 4900, SCREEN_HEIGHT / 6 - 10);
	App->enemies->AddEnemy(ENEMY_TYPES::Spider, 4900, SCREEN_HEIGHT - 60);

	return true;
}

// UnLoad assets
bool ModuleLevel4::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(backgroundtilemap);
	App->textures->Unload(foregroundtilemap1);
	App->textures->Unload(foregroundtilemap2);
	App->textures->Unload(BackLavaAnim);
	App->textures->Unload(wall);
	App->textures->Unload(pinchywall);
	
	App->audio->UnloadMusic(main_track_lvl4);
	App->audio->UnloadMusic(boss_track_lvl4);

	App->player->Disable();
	App->enemies->Disable();
	App->scores->Disable();
	App->UI->Disable();

	

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}

// Update: draw background
update_status ModuleLevel4::Update()
{
	App->boss4->Enable();

	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN)
	{
		App->render->camera.x += 100;
		App->player->position.x += 100;
		
	}
	
	//Player respawning
	if (App->player2->IsEnabled() == false && App->player2->life != 0)
	{
		App->player2->life = 0;
	}

	if (App->player->IsEnabled() == false && App->player->life != 0)
	{
		App->player->life = 0;
	}

	// Move camera forward -----------------------------

	if (App->render->camera.x < 5050)
	{
		App->render->camera.x += 1 * SCREEN_SIZE;

		App->player->position.x += 1;

		if (App->player2->IsEnabled() == true)
			App->player2->position.x += 1;

	}

	if (!boss_fight && bosstime==false)
		App->audio->PlayMusic(main_track_lvl4,ONCE);
	
	//if (boss_fight)
	//	App->audio->PlayMusic(boss_track_lvl4,ONCE);
	//
	//if (SDL_GetTicks() - start_time >= 202000 && !boss_fight) //After 202 seconds, the music changes from the maintrack to the boss track
	//{
	//	App->audio->StopAudio();
	//	boss_fight = true;
	//}

	if (App->render->camera.x >= 5050 && bosstime == false)
	{
		App->audio->StopAudio();
		App->audio->PlayMusic(boss_track_lvl4, ONCE);
		bosstime = true;
	}
	
	
	if (App->player->IsEnabled() == false && App->player2->IsEnabled() == false )
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
	if (maxreached == false && wallmovdownposition.y <= -60)
	{
		wallmovdownposition.y += 1;
		
	

		if (wallmovdownposition.y == -60)
			maxreached = true;
	}
	if (maxreached == true && wallmovdownposition.y <= -60)
	{
		wallmovdownposition.y -= 1;
		

		if (wallmovdownposition.y == -150)
			maxreached = false;
	}

	///////////////////////////////////////////////////

	if (maxreached == false && wallmovdownposition2.y <= -60)
	{
		wallmovdownposition2.y += 1;



		if (wallmovdownposition2.y == -60)
			maxreached = true;
	}
	if (maxreached == true && wallmovdownposition2.y <= -60)
	{
		wallmovdownposition2.y -= 1;


		if (wallmovdownposition2.y == -150)
			maxreached = false;
	}

	////////////////////////////////////////////////////

	if (maxreached == false && wallmovdownposition3.y <= -60)
	{
		wallmovdownposition3.y += 1;



		if (wallmovdownposition3.y == -60)
			maxreached = true;
	}
	if (maxreached == true && wallmovdownposition3.y <= -60)
	{
		wallmovdownposition3.y -= 1;


		if (wallmovdownposition3.y == -100)
			maxreached = false;
	}


	//////////////////////////////////////////////////////////

	if (maxreached == false && wallmovdownposition4.y <= -60)
	{
		wallmovdownposition4.y += 1;



		if (wallmovdownposition4.y == -60)
			maxreached = true;
	}
	if (maxreached == true && wallmovdownposition4.y <= -60)
	{
		wallmovdownposition4.y -= 1;


		if (wallmovdownposition4.y == -100)
			maxreached = false;
	}

	/////////////////////////////////////////////////////////////
	colliderwallmovdown->SetPos(wallmovdownposition.x+1500, wallmovdownposition.y);
	colliderwallmovdown2->SetPos(wallmovdownposition.x + 1600, wallmovdownposition.y);
	colliderwallmovdown3->SetPos(wallmovdownposition.x + 1700, wallmovdownposition.y);
	colliderwallmovdown4->SetPos(wallmovdownposition.x + 1300, wallmovdownposition.y);
	//End of Wall movement

	//Pinchy Walll movement

	if (maxreachedpinchy == false && pinchywallposition.y+100 >= SCREEN_HEIGHT)
	{
		pinchywallposition.y -= 1;


		if (pinchywallposition.y+100 == SCREEN_HEIGHT)
			maxreachedpinchy = true;
	}
	if (maxreachedpinchy == true && pinchywallposition.y <= SCREEN_HEIGHT)
	{
		pinchywallposition.y += 1;


		if (pinchywallposition.y == SCREEN_HEIGHT)
			maxreachedpinchy = false;
	}

	/////////////////////////////////////////

	if (maxreachedpinchy == false && pinchywallposition2.y + 100 >= SCREEN_HEIGHT)
	{
		pinchywallposition2.y -= 1;


		if (pinchywallposition2.y + 100 == SCREEN_HEIGHT)
			maxreachedpinchy = true;
	}
	if (maxreachedpinchy == true && pinchywallposition2.y <= SCREEN_HEIGHT)
	{
		pinchywallposition2.y += 1;


		if (pinchywallposition2.y == SCREEN_HEIGHT)
			maxreachedpinchy = false;
	}


	/////////////////////////////////////////

	if (maxreachedpinchy == false && pinchywallposition3.y + 150 >= SCREEN_HEIGHT)
	{
		pinchywallposition3.y -= 1;


		if (pinchywallposition3.y + 150 == SCREEN_HEIGHT)
			maxreachedpinchy = true;
	}
	if (maxreachedpinchy == true && pinchywallposition3.y <= SCREEN_HEIGHT)
	{
		pinchywallposition3.y += 1;


		if (pinchywallposition3.y == SCREEN_HEIGHT)
			maxreachedpinchy = false;
	}

	/////////////////////////////////////////

	if (maxreachedpinchy == false && pinchywallposition4.y + 150 >= SCREEN_HEIGHT)
	{
		pinchywallposition4.y -= 1;


		if (pinchywallposition4.y + 150 == SCREEN_HEIGHT)
			maxreachedpinchy = true;
	}
	if (maxreachedpinchy == true && pinchywallposition4.y <= SCREEN_HEIGHT)
	{
		pinchywallposition4.y += 1;


		if (pinchywallposition4.y == SCREEN_HEIGHT)
			maxreachedpinchy = false;
	}

	//////////////////////////////////////

	colliderpinchywall->SetPos(pinchywallposition.x+1500, pinchywallposition.y);
	colliderpinchywall2->SetPos(pinchywallposition.x + 1600, pinchywallposition.y);
	colliderpinchywall3->SetPos(pinchywallposition.x + 1700, pinchywallposition.y);
	colliderpinchywall4->SetPos(pinchywallposition.x + 1300, pinchywallposition.y);
	//End of Pinchy Wall movement
	
	// Draw everything --------------------------------------
	App->render->Blit(backgroundtilemap, 0, 0, &backgroundtilemaprect, 0.5); // back background
	App->render->Blit(BackLavaAnim, 0, 0, &Back_Lava.GetCurrentFrame(), 0.5); // back lava animation

	//WALLS
	App->render->Blit(wall, wallmovdownposition.x+1500, wallmovdownposition.y, &wallrect, 1);
	App->render->Blit(pinchywall, pinchywallposition.x+1500, pinchywallposition.y, &pinchywalanim.GetCurrentFrame());

	App->render->Blit(wall, wallmovdownposition2.x + 1600, wallmovdownposition2.y, &wallrect, 1);
	App->render->Blit(pinchywall, pinchywallposition2.x + 1600, pinchywallposition2.y, &pinchywalanim.GetCurrentFrame());

	App->render->Blit(wall, wallmovdownposition3.x + 1700, wallmovdownposition3.y, &wallrect, 1);
	App->render->Blit(pinchywall, pinchywallposition3.x + 1700, pinchywallposition3.y, &pinchywalanim.GetCurrentFrame());

	App->render->Blit(wall, wallmovdownposition4.x + 1300, wallmovdownposition4.y, &wallrect, 1);
	App->render->Blit(pinchywall, pinchywallposition4.x + 1300, pinchywallposition4.y, &pinchywalanim.GetCurrentFrame());

	App->render->Blit(foregroundtilemap1, 0, 0, &foregroundtilemaprect1, 1); //foregorund
	App->render->Blit(foregroundtilemap2, 4100, 0, &foregroundtilemaprect2, 1); //foregorund
	App->render->Blit(Enemies_1, 400, 100, &op_cannon.GetCurrentFrame(), 1);

//----------------------platforms--------------------------


	/*App->render->Blit(foreground_platform, 2760, -120, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, -80, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, -40, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, 20, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, 60, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, 140, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, 180, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, 100, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, 220, &foreground_platforms, 1);
App->render->Blit(foreground_platform, 2760, 260, &foreground_platforms, 1);*/

	

//	App->render->Blit(foreground_platform, 2760, 100, &platform_up.GetCurrentFrame(), 1);
	
	//App->render->Blit(foreground_platform, 2860, -90, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, -50, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, -10, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, 30, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, 70, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, 110, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, 150, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, 190, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, 230, &foreground_platforms, 1);
	//App->render->Blit(foreground_platform, 2860, 270, &foreground_platforms, 1);


//	App->render->Blit(foreground_platform, 2860, 110, &platform_down.GetCurrentFrame(), 1);
//-----------------------------------------------------------------------------------


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