#ifndef __POWERUPHOLDER_H__
#define __POWERUPHOLDER_H__

#include "Enemy.h"

class PowerUpHolder : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation walk;
	Animation fly;

public:

	PowerUpHolder(int x, int y);

	void Move();
};

#endif // __POWERUPHOLDER_H__