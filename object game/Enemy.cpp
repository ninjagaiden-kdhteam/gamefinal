#include "Enemy.h"

Enemy::Enemy(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance)
{
	this->id = id;
	this->type = (Type)type;
	this->position = D3DXVECTOR3(x, y, 0);
	this->direction = direction;
	this->leftX = (float)leftX;
	this->rightX = (float)rightX;
	this->distance = (float)distance;
	this->initdirection = direction;
	this->initposition = position;
}

Enemy::~Enemy()
{
}