#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "GameObject.h"

class Enemy :public GameObject
{
protected:
	//khoảng cách so với ninja để enemy xuất hiện
	float distance;
	//biên trái phải mà enemy có thể di chuyển
	int leftX, rightX;
public:
	Enemy(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance);
	float GetDistance() { return this->distance; }
	~Enemy();
};
#endif // !__ENEMY_H__