#include "Animation.h"



void Animation::AddFrame(int id)
{
	int t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(id);
	frames.push_back(sprite);
}


void Animation::Render(float x, float y, int  &lienTuc, int direction, float &xx, float &yy,int &w,int &h,int backFrame,int alpha,int setFrame, bool isRenderOnlyFrame)
{
	if ((!IsTimeFreeze && !IsNinjaDie && !IsGamePause) || (IsTimeFreeze && isRenderOnlyFrame == false))// istimefreeze=true vs isRenderOnlyFrame==false là ninja và container butterfly
	{
		DWORD now = GetTickCount();
		if (currentFrame == -1)
		{
			currentFrame = 0;
			lastFrameTime = now;
		}
		else
		{
			DWORD t = defaultTime;
			if (now - lastFrameTime > t)
			{
				currentFrame++;
				lastFrameTime = now;

				if ((lienTuc == 1) && (frames.size() == currentFrame))
				{
					currentFrame = 0; 
					lienTuc = 0; //tắt biến cờ liên tục
					return;
				}
				
				if (currentFrame == frames.size()) currentFrame = 0;
			}

		}

		if (setFrame != -1) currentFrame = setFrame;
	}

	else
	{
		//khi đóng băng thời gian, có con ninja và butterfly vẫn render nhiều frame
		//khi đóng băng thời gian, khi ninja chết, khi dừng game render một frame
		if (IsTimeFreeze && isRenderOnlyFrame == true || IsNinjaDie || IsGamePause)
		{
			if (alpha == NHAY_MOTMAU) alpha = KHONG_NHAY;
			if (currentFrame == -1 || currentFrame >= frames.size())
				currentFrame = 0;
		}
	}

	
	w = frames[currentFrame]->GetWidth();
	h = frames[currentFrame]->GetHeight();
	//lấy độ xê dịch
	float dx = 0;
	float dy = 0;
	yy =dy= frames[currentFrame]->GetDy();
	xx =dx= frames[currentFrame]->GetDx();
	frames[currentFrame]->Render(x,y, dx, dy, direction, backFrame,alpha);

}