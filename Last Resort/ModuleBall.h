#ifndef __ModuleBall_H__
#define __ModuleBall_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h" 

class ModuleBall :public Module
{
public:
	ModuleBall();
	~ModuleBall();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	void ModuleBall::Move();

public:
	iPoint position;
private:
	Animation blueball_0;
	Animation blueball_45;
	Animation blueball_90;
	Animation blueball_135;
	Animation blueball_180;

	Animation blueball_225;
	Animation blueball_270;
	Animation blueball_315;
};
#endif // !1
