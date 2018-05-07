#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleBall.h"


ModuleSceneIntro::ModuleSceneIntro()
{
	introrect.x = 0;
	introrect.y = 0;
	introrect.w = 320;
	introrect.h = 224;
	
	intro_neogeo.Reset();
	max330.Reset();
	mega_pro.Reset();
	SNK.Reset();
	C_sprite.Reset();

	//NeoGeo
	intro_neogeo.PushBack({ 0, 0, 39, 40 });
	intro_neogeo.PushBack({ 38, 0, 39, 40 });
	intro_neogeo.PushBack({ 77, 0, 66, 40 });
	intro_neogeo.PushBack({ 143, 0, 68, 40 });
	intro_neogeo.PushBack({ 211, 0, 85, 40 });
	intro_neogeo.PushBack({ 296, 0, 100, 40 });
	intro_neogeo.PushBack({ 396, 0, 112, 40 });
	intro_neogeo.PushBack({ 508, 0, 127, 40 });
	intro_neogeo.PushBack({ 635, 0, 141, 40 });
	intro_neogeo.PushBack({ 776, 0, 156, 40 });
	intro_neogeo.PushBack({ 0, 40, 168, 40 });
	intro_neogeo.PushBack({ 169, 40, 186, 40 });
	intro_neogeo.PushBack({ 355, 40, 199, 40 });
	intro_neogeo.PushBack({ 554, 40, 210, 40 });
	intro_neogeo.PushBack({ 766, 40, 227, 40 });
	intro_neogeo.PushBack({ 0, 82, 227, 36 });
	intro_neogeo.PushBack({ 227, 82, 227, 36 });
	intro_neogeo.PushBack({ 454, 82, 227, 36 });
	intro_neogeo.PushBack({ 681, 82, 227, 36 });
	intro_neogeo.PushBack({ 0, 118, 227, 28 });
	intro_neogeo.PushBack({ 227, 118, 227, 28 });
	intro_neogeo.PushBack({ 454, 118, 227, 28 });
	intro_neogeo.PushBack({ 681, 118, 227, 28 });
	intro_neogeo.PushBack({ 0, 146, 227, 18 });
	intro_neogeo.PushBack({ 227, 146, 227, 18 });
	intro_neogeo.PushBack({ 454, 146, 224, 18 });
	intro_neogeo.PushBack({ 678, 146, 227, 18 });
	intro_neogeo.PushBack({ 0, 164, 224, 9 });
	intro_neogeo.PushBack({ 227, 164, 221, 9 });
	intro_neogeo.PushBack({ 454, 164, 227, 9 });
	intro_neogeo.PushBack({ 680, 164, 227, 9 });
	intro_neogeo.PushBack({ 0, 387, 221, 9 });
	intro_neogeo.PushBack({ 221, 387, 224, 9});
	intro_neogeo.PushBack({ 446, 387, 224, 9 });
	intro_neogeo.PushBack({ 670, 387, 227, 10 });
	intro_neogeo.PushBack({ 0, 399, 227, 12 });
	intro_neogeo.PushBack({ 227, 399, 224, 19 });
	intro_neogeo.PushBack({ 454, 399, 224, 19});
	intro_neogeo.PushBack({ 681, 399, 227, 19 });
	intro_neogeo.PushBack({ 0, 419, 227, 29 });
	intro_neogeo.PushBack({ 227, 419, 227, 29 });
	intro_neogeo.PushBack({ 454, 419, 227, 29 });
	intro_neogeo.PushBack({ 681, 419, 227, 29 });
	intro_neogeo.PushBack({ 0, 448, 227, 40 });
	intro_neogeo.PushBack({ 227, 448, 227, 40 });
	intro_neogeo.PushBack({ 454, 448, 227, 40 });
	intro_neogeo.PushBack({ 681, 448, 227, 40 });
	intro_neogeo.loop = false;
	intro_neogeo.speed = 0.5f;

	//Max330
	max330.PushBack({ 0, 0, 10, 15 });
	max330.PushBack({ 0, 0, 20, 15 });
	max330.PushBack({ 0, 0, 30, 15 });
	max330.PushBack({ 0, 0, 40, 15 });
	max330.PushBack({ 0, 0, 50, 15 });
	max330.PushBack({ 0, 0, 60, 15 });
	max330.PushBack({ 0, 0, 70, 15 });
	max330.PushBack({ 0, 0, 80, 15 });
	max330.PushBack({ 0, 0, 90, 15 });
	max330.PushBack({ 0, 0, 100, 15 });
	max330.PushBack({ 0, 0, 110, 15 });
	max330.PushBack({ 0, 0, 120, 15 });
	max330.PushBack({ 0, 0, 130, 15 });
	max330.PushBack({ 0, 0, 133, 15 });
	max330.loop = false;
	max330.speed = 0.3f;

	//MegaPro
	mega_pro.PushBack({ 0, 0, 10, 15 });
	mega_pro.PushBack({ 0, 0, 20, 15 });
	mega_pro.PushBack({ 0, 0, 30, 15 });
	mega_pro.PushBack({ 0, 0, 40, 15 });
	mega_pro.PushBack({ 0, 0, 50, 15 });
	mega_pro.PushBack({ 0, 0, 60, 15 });
	mega_pro.PushBack({ 0, 0, 70, 15 });
	mega_pro.PushBack({ 0, 0, 80, 15 });
	mega_pro.PushBack({ 0, 0, 90, 15 });
	mega_pro.PushBack({ 0, 0, 100, 15 });
	mega_pro.PushBack({ 0, 0, 110, 15 });
	mega_pro.PushBack({ 0, 0, 120, 15 });
	mega_pro.PushBack({ 0, 0, 130, 15 });
	mega_pro.PushBack({ 0, 0, 133, 15 });
	mega_pro.loop = false;
	mega_pro.speed = 0.3f;

	//SNK
	SNK.PushBack({ 216, 0, 72, 18 });
	SNK.PushBack({ 288, 0, 72, 18 });
	SNK.PushBack({ 360, 0, 72, 18 });
	SNK.PushBack({ 432, 0, 72, 18 });
	SNK.PushBack({ 0, 19, 72, 18 });
	SNK.PushBack({ 72, 19, 72, 18 });
	SNK.PushBack({ 144, 19, 72, 18 });
	SNK.PushBack({ 216, 19, 72, 18 });
	SNK.PushBack({ 288, 19, 72, 18 });
	SNK.PushBack({ 360, 19, 72, 18 });
	SNK.PushBack({ 432, 19, 72, 18 });
	SNK.PushBack({ 0, 38, 72, 18 });
	SNK.PushBack({ 72, 38, 72, 18 });
	SNK.PushBack({ 144, 38, 72, 18 });
	SNK.PushBack({ 216, 38, 72, 18 });
	SNK.PushBack({ 288, 38, 72, 18 });
	SNK.PushBack({ 360, 38, 72, 18 });
	SNK.loop = false;
	SNK.speed = 0.3f;

	//C
	C_sprite.PushBack({ 693, 928, 240, 40 });
	C_sprite.PushBack({ 693, 928, 240, 40 });
	C_sprite.PushBack({ 693, 928, 240, 40 });
	C_sprite.PushBack({ 693, 928, 240, 40 });
	C_sprite.PushBack({ 693, 928, 240, 40 });
	C_sprite.speed = 0.1f;

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading intro");
	
	introbackground = App->textures->Load("assets/sprites/Intro_Neogeo/Title_Neogeo_Begining_Sprite.png");
	Max330 = App->textures->Load("assets/sprites/Intro_Neogeo/MAX_330.png");
	MegaPro = App->textures->Load("assets/sprites/Intro_Neogeo/MegaPro.png");
	SNK_Logo = App->textures->Load("assets/sprites/Intro_Neogeo/SNK_Beginning_Sprite.png");
	LastResort = App->textures->Load("assets/sprites/Last_Resort_Intro.png");

	maintrackintro = App->audio->LoadMusic("assets/music/1.Last resort title.ogg");
	
	App->render->camera.x = App->render->camera.y = 0;

	current_animation = &intro_neogeo;
	
	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(introbackground);
	App->textures->Unload(Max330);
	App->textures->Unload(MegaPro);
	App->textures->Unload(SNK_Logo);
	App->textures->Unload(LastResort);

	/*App->audio->StopAudio();*/
	App->audio->UnloadMusic(maintrackintro);
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->audio->PlayMusic(maintrackintro, ONCE);


	// Draw everything --------------------------------------
		
	
	App->render->Blit(introbackground, 50 , 50, &(intro_neogeo.GetCurrentFrame()));
		
	if (intro_neogeo.Finished()){
		App->render->Blit(Max330, 90, 100, &(max330.GetCurrentFrame()));
		}
	if (max330.Finished()) {
		App->render->Blit(MegaPro, 90, 115, &(mega_pro.GetCurrentFrame()));
		}
	if (mega_pro.Finished()) {
		App->render->Blit(SNK_Logo, 125, 150, &(SNK.GetCurrentFrame()));
		}
	if (SNK.Finished()) {
		App->render->Blit(introbackground, 49, 50, &(C_sprite.GetCurrentFrame()));
	}
	if (C_sprite.Finished()) {
		App->render->Blit(LastResort, 0, 0, &introrect);
	}
	

	if(App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN && App->fade->IsFading() == false)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, (Module*)App->level4); 
		App->audio->StopAudio();
	}

	return UPDATE_CONTINUE;
}