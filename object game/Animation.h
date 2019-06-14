#pragma once
#include <Windows.h>
#include <vector>
#include "Sprites.h"


using namespace std;
class Animation
{
	DWORD lastFrameTime; 
	float defaultTime; //thời gian giữa 2 frame liền kề
	int currentFrame;

	vector<LPSPRITE> frames;
public:
	int GetCurrentFrame() { return currentFrame; } //lấy frame hiện tại của animation
	Animation(float time){ this->defaultTime = time; lastFrameTime = -1; currentFrame = -1; }
	void AddFrame(int id);//thêm một frame vào animation
	void Render(float x, float y, int &lienTuc, int direction,float &xx, float &yy,int &w,int &h, int backFrame=-1,int alpha=KHONG_NHAY,int setFrame=-1, bool isRenderOnlyFrame = true);

};

typedef Animation* LPANIMATION;

