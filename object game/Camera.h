#pragma once
#include <d3dx9.h>
#include "GameDefinitions.h"
class Camera
{
	D3DXVECTOR3 position;
	static Camera * __instance;
	int width, height;
public:
	Camera();
	void Initialize(float x, float y, int width = GAME_WIDTH, int height = GAME_HEIGHT);
	//Chuyển đổi tọa độ trong thế giới thực sang tọa độ viewport
	D3DXVECTOR3 Transform(D3DXVECTOR3 p);
	void SetPosition(float x, float y);
	D3DXVECTOR3 GetPosition();
	void Update(D3DXVECTOR3 p);
	static Camera * GetInstance();
	~Camera();
};

