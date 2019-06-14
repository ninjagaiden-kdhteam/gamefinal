#ifndef _BIRD_H_
#define _BIRD_H_
#include "Enemy.h"
#include "Ninja.h"
#define BIRD_SPEED 0.07f
class Bird :public Enemy
{
	//hệ số phương trình bay
	float a;
	float b;
	int isInNinja;
	float change; //Biên để đổi hướng bay
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	Bird(int id, int type, int x, int y, int direction,int leftX,int rightX, int distance);
	~Bird();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetActive(int x);
	void CaculateAB(float x,float y);
	void CaculateABwithNinja();
};
#endif // !_BIRD_H

