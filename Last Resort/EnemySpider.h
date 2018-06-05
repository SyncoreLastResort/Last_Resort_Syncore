#ifndef __ENEMY_SPIDER_H__
#define __ENEMY_SPIDER_H__

#include "Enemy.h"

class EnemySpider : public Enemy
{
private:

	float wave = -90.0f;
	bool going_up = true;
	Animation fly;

public:
	bool going_left = true;
	int original_y = 0;
	int counter = 0;
	int angle;
	int angle2;
	double radians;
	double radians2;

	Animation left_top;
	Animation right_top;
	Animation left_bottom;
	Animation right_bottom;
	fPoint shoot;
	iPoint PlayerPosition;

	EnemySpider(int x, int y);
	void Move();

};

#endif // __ENEMY_SPIDER_H__