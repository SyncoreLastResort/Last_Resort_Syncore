#ifndef __POWERUPHOLDER_H__
#define __POWERUPHOLDER_H__

#include "Enemy.h"
#include "Path.h"

class PowerUpHolder : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	Animation walk;
	Animation fly;
	Path powerupholderpath;
	Path powerupholderpath2;
	uint changeanim = 1;
	/*int counterposx = 0;*/

public:

	PowerUpHolder(int x, int y);

	void Move();
};

#endif // __POWERUPHOLDER_H__