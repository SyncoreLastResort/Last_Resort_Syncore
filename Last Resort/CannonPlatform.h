#ifndef __CANNON_PLATFORM_H__
#define __CANNON_PLATFORM_H__

#include "Enemy.h"

class CannonPlatform : public Enemy
{

public:
	int counter = 0;
	bool shot = false;
	Animation shooting;
	Animation idle;

	CannonPlatform(int x, int y);
	void Move();

};

#endif // __ENEMY_SPIDER_H__