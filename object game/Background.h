#pragma once
#include "Camera.h"
#include "Sprite.h"
#include "Textures.h"
#include <fstream>

#define ROW 
#define COLUMN 
class Background
{
	static int numBackGround; //số thứ tự của background đang vẽ, giá trị =1,2,3 tương ứng với từng map 1,2,3
	int **matrixMap; //ma trận 2 chiều, chứa nội dung file matrix.txt để vẽ background
	int row;
	int maxColumn;


	int leftFrame; //chứa chỉ số cột trái của background
	int rightFrame; //chứa chỉ số cột phải của background
	Sprite* backGroundSprite; //lưu sprite của map 1,2 hoặc 3
	LPDIRECT3DTEXTURE9 tileMap1;
	LPDIRECT3DTEXTURE9 tileMap2;
	LPDIRECT3DTEXTURE9 tileMap3;
public:
	Background(int num = 0);
	void setNumBG(int num) { numBackGround = num; }
	void Update(DWORD dt);
	void Draw(int alpha=KHONG_NHAY);//alpha để chọn màu vẽ background
	void readMatrix();
	static int getNumBackGround() { return numBackGround; }
	~Background();
};

