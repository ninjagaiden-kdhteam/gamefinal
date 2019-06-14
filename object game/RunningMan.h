#ifndef __RUNNINGMAN_H__
#define __RUNNINGMAN_H__
#include "Enemy.h"


class RunningMan :public Enemy
{
public:
	RunningMan(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	~RunningMan();
};
#endif // !__RUNNINGMAN_H__