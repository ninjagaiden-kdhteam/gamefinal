#include "Animation.h"



void Animation::AddFrame(int id)
{
	int t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(id);
	frames.push_back(sprite);
}

/*các thông số của hàm render:
x,y: tọa độ, vị trí render animation trên game
lienTuc: đổi tên từ isHitting cũ, khi lienTuc=1: animation sẽ được render cho hết các sprite, vd: đánh là 3 sprite
direction: hướng của vật
xx,yy: tham số truyền vào để lấy dx,dy của sprite được render trong animation hiện tại
w,h: tham số truyền vào để lấy chiều rộng, cao của sprite được render hiện tại
backFrame: =1 nếu hàm render này đang vẽ background, =0: là ngược lại
alpha: mặc định là KHONG_NHAY(0) là vẽ bình thường, NHAY_MOTMAU(1) là vẽ mờ hình đi khi ninja bị tấn công, giá trị khác cũng vẽ bình thường
setFrame: là thứ tự frame, object truyền vào setFrame!=-1 tức là nó muốn vẽ frames[setFrame] ra
*/

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
					currentFrame = 0; //đã thực hiện xong chuỗi frame liên tục
					lienTuc = 0; //tắt biến cờ liên tục
					return;
				}
				//thực hiện hết chuỗi sprite của animation, về lại sprite thứ 0
				if (currentFrame == frames.size()) currentFrame = 0;
			}

		}

		//nếu setFrame có giá trị, currentFrame gán bằng setFrame ngay
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

	//lấy w và h hiện tại của sprite được render
	w = frames[currentFrame]->GetWidth();
	h = frames[currentFrame]->GetHeight();
	//lấy độ xê dịch
	//tạo cặp biến chứa độ lệch của sprite
	float dx = 0;
	float dy = 0;
	yy =dy= frames[currentFrame]->GetDy();
	xx =dx= frames[currentFrame]->GetDx();
	frames[currentFrame]->Render(x,y, dx, dy, direction, backFrame,alpha);

}