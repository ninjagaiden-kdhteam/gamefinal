#include "Camera.h"

Camera * Camera::__instance = NULL;

Camera::Camera()
{
}

void Camera::Initialize(float x, float y, int width, int height)
{
	position.x = x;
	position.y = y;
	position.z = 0;
	this->width = width;
	this->height = height;
}

D3DXVECTOR3 Camera::Transform(D3DXVECTOR3 p)
{
	//Trong giáo trình
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -this->position.x;
	mt._42 = this->position.y;
	D3DXVECTOR4 tmp;
	D3DXVec3Transform(&tmp, &p, &mt);
	return D3DXVECTOR3(tmp.x, tmp.y, 0);
}

void Camera::SetPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return this->position;
}


void Camera::Update(D3DXVECTOR3 p)
{
	//vị trí camera += độ dời vị trí của nhân vật
	Camera::GetInstance()->SetPosition(p.x - GAME_WIDTH / 2, GAME_HEIGHT);
}

Camera * Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}

Camera::~Camera()
{
}
