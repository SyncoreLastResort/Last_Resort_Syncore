#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_SOUNDS 50


class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();
    update_status Update();

	Mix_Music* const Load(const char* path);


public:
	bool isplaying = false;
	Mix_Music* audio[MAX_SOUNDS];
	uint last_sound = 0;

	//Sounds

	Mix_Music* maintrack = nullptr;
};

#endif // __ModuleAudio_H__