#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25



class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame = 0;
	int last_frame = 0;
	
public:

	void setcurrentframe() 
	{ 
		if (current_frame > 0)
		{
			current_frame--;

		}
	}

	void PushBack(const SDL_Rect& rect, int maximumframe)
	{
		frames[last_frame++] = rect;
	}

	
	SDL_Rect& GetCurrentFrame()
	{

		current_frame += speed;
		if (current_frame >= last_frame) 
			current_frame = (float)last_frame - 1;
		
		return frames[(int)current_frame];
	}
	
};


#endif