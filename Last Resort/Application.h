#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleAudio;
class ModuleCongrats;
class ModuleLevel2;
class ModuleLevel1;
class ModuleIntroScene;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;

// TODO 1: Create an intro scene with rtype/intro.png that then fades to ModuleSpaceScene

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleCongrats* congrats;
	ModuleLevel2* level2;
	ModuleLevel1* level1;
	ModuleIntroScene* intro;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleAudio* audio;

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