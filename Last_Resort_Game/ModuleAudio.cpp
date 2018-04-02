#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )



ModuleAudio::ModuleAudio() : Module()
{
	for (uint i = 0; i < MAX_SOUNDS; ++i)
	{
		audio[i] = nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{
	LOG("Init Audio library");
	bool ret = true;

	// Now it's time for some audio

	// Create mixer --
	int flags = Mix_Init(MIX_INIT_OGG);
	if (!flags)
	{
		LOG("Could not init mixer SDL Error: %s \n", SDL_GetError());
		bool ret = false;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); //frequency, format, channels, chunk

	Load("assets/sounds/LRMusic.ogg");
	return ret;
}

update_status ModuleAudio::Update()
{
	if (!isplaying)
	{
		Mix_PlayMusic(audio[0], -1);
		isplaying = true;
	}

	return update_status::UPDATE_CONTINUE;
}


// Called before q	uitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing audio and Mixer library");

	for (uint i = 0; i < MAX_SOUNDS; ++i)
	{
		if (audio[i] != nullptr)
			Mix_FreeMusic(audio[i]);
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

// Load new texture from file path
Mix_Music* const ModuleAudio::Load(const char* path)
{
	Mix_Music* music = nullptr;

	music = Mix_LoadMUS(path);

	if (!music)
	{
		LOG("Unable to create music from path! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		audio[last_sound++] = music;
	}


	return music;
}