#ifndef __ENEMY_WASP_H__
#define __ENEMY_WASP_H__

#include "Enemy.h"

class Enemy_Wasp : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Wasp(int x, int y);

	void Move();
};

#endif // __ENEMY_WASP_H__