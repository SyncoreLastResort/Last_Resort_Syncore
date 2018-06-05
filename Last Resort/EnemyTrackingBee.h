#ifndef __ENEMY_BEE_H__
#define __ENEMY_BEE_H__

#include "Enemy.h"

class EnemyTrackingBee : public Enemy
{
private:

	float wave = -90.0f;
	bool going_up = true;
	Animation fly;

public:

	int angle;
	double radians;
	int counter;
	double radians2;
	int angle2;
	fPoint shoot;

	Animation Front;
	Animation Front_left;
	Animation Front_mid_Left;
	Animation After_Left;
	Animation Left;
	Animation Before_Left;
	Animation mid_Left;
	Animation Back_Left;
	Animation Back;
	Animation Back_Right;
	Animation Back_mid_Right;
	Animation Before_Right;
	Animation Right;
	Animation After_Right;
	Animation Front_mid_Right;
	Animation Front_Right;

	iPoint PlayerPosition;







	EnemyTrackingBee(int x, int y);
	void Move();

};

#endif // __ENEMY_BEE_H__
