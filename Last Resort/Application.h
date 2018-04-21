#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 19

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleFonts;
class ModuleRender;
class ModuleParticles;
class ModuleAudio;
class ModuleCongrats;
class ModuleGameOver;
class ModuleLevel2;
class ModuleLevel1;
class ModuleSceneIntro;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleEnemies;
class ModuleFirstBoss;
class Module;
class ModuleBall;
class ModuleBall2;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleFonts* fonts;
	ModuleCongrats* congrats;
	ModuleGameOver* gameover;
	ModuleLevel2* level2;
	ModuleLevel1* level1;
	ModuleSceneIntro* scene_intro;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleAudio* audio;
	ModuleEnemies* enemies;
	ModuleFirstBoss* boss1;
	ModuleBall* ball_player1;
	ModuleBall2* ball_player2;

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