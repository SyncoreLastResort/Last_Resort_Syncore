#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleScores.h"
#include "ModuleLevel4.h"
#include "ModuleSceneIntro.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include "ModuleBall.h"
#include "ModuleBall2.h"
#include "ModuleUI.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = level4 = new ModuleLevel4();
	modules[i++] = scores = new ModuleScores();
	modules[i++] = stageclear = new ModuleStageClear();
	modules[i++] = gameover = new ModuleGameOver();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = ball_player1 = new ModuleBall();
	modules[i++] = ball_player2 = new ModuleBall2();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = particles = new ModuleParticles();
	
	modules[i++] = scene_intro = new ModuleSceneIntro();
	modules[i++] = UI = new ModuleUI();
	modules[i++] = fade = new ModuleFadeToBlack();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Deactivate modules here ----
	player2->Disable();
	player->Disable();
	enemies->Disable();
	gameover->Disable();
	stageclear->Disable();
	scores->Disable();
	level4->Disable();
	ball_player1->Disable();
	ball_player2->Disable();

	// ----------------------------

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}