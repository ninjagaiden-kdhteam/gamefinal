#include "Background.h"



int Background::numBackGround = 1;

void Background::readMatrix()
{
	string path;

	switch (numBackGround)
	{
	case 1:
		path = "textures//matrix1.txt";
		backGroundSprite = new Sprite(tileMap1);
		break;
	case 2:
		path = "textures//matrix2.txt";
		backGroundSprite = new Sprite(tileMap2);
		break;
	case 3:
		path = "textures//matrix3.txt";
		backGroundSprite = new Sprite(tileMap3);
		break;
	default:
		break;
	}
	fstream fs(path.c_str());

	//đọc nội dung file ma trận
	int Tiles;
	fs >> Tiles >> row >> maxColumn;

	matrixMap = new int *[row];
	for (int i = 0; i < row; i++)
	{
		matrixMap[i] = new int[maxColumn];
		for (int j = 0; j < maxColumn; j++)
		{
			fs >> matrixMap[i][j];
		}
	}
	fs.close();
}


Background::Background(int num)
{
	//get dự phòng cả 3 tileSet của 3 map để chuẩn bị vẽ
	tileMap1 = Textures::GetInstance()->Get(1);
	tileMap2 = Textures::GetInstance()->Get(2);
	tileMap3 = Textures::GetInstance()->Get(3);
	numBackGround = num; 
	Background::readMatrix(); //đọc ma trận background của map
}

void Background::Update(DWORD dt)
{
	int x = Camera::GetInstance()->GetPosition().x;
	leftFrame = x / SIZE_TILE_SET;
	rightFrame = (x + GAME_WIDTH) / SIZE_TILE_SET;
	//khi vẽ sẽ vẽ từ background[left]->background[right]
}

void Background::Draw(int alpha)
{
	int x = Camera::GetInstance()->GetPosition().x;
	//render những tile có trong khung hình
	for (int r = 0; r < row; r++)
	{
		int count = 0;
		//cột từ left->right
		for (int c = leftFrame; c <= rightFrame; c++)
		{
			//r * SIZE_TILE_SET+20: cộng thêm 20 để hạ vị trí vẽ xuống bớt, xóa "+20" rồi run game sẽ hiểu
			backGroundSprite->Render((float)(c*SIZE_TILE_SET - x), r * SIZE_TILE_SET+20, 0, 0, 0, matrixMap[r][c],alpha);
			count++;
		}
	}
}

Background::~Background()
{
}
