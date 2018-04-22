#ifndef __ENEMY_POWERUP_H__
#define __ENEMY_POWERUP_H__

#include "Enemy.h"

class Power_Up : public Enemy
{
private:
	float wave = -1.0f;
	/*bool going_up = true;*/
	int original_y = 0;
	Animation Powerup;

public:

	Power_Up(int x, int y);

	/*void Move();*/
};

#endif // __POWERUP_H__