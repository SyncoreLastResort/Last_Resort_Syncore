#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleFonts;
class ModuleRender;
class ModuleParticles;
class ModuleAudio;
class ModuleScores;
class ModuleStageClear;
class ModuleGameOver;
class ModuleLevel4;
class ModuleSceneIntro;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleEnemies;
class Module;
class ModuleBall;
class ModuleBall2;
class ModuleBoss4;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleFonts* fonts;
	ModuleScores* scores;
	ModuleStageClear* stageclear;
	ModuleGameOver* gameover;
	ModuleLevel4* level4;
	ModuleSceneIntro* scene_intro;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleAudio* audio;
	ModuleEnemies* enemies;
	ModuleBall* ball_player1;
	ModuleBall2* ball_player2;
	ModuleBoss4* boss4;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__