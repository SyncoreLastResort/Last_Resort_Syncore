#ifndef __ENEMY_BROWNCOOKIE_H__
#define __ENEMY_BROWNCOOKIE_H__

#include "Enemy.h"
#include "Path.h"
#include "p2Point.h"

class EnemyBrownCookie : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	Animation fly;
	Path browncookiepath;

public:

	EnemyBrownCookie(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNCOOKIE_H__
