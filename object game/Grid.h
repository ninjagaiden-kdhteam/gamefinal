#ifndef __GRID_H__
#define __GRID_H__

#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include "debug.h"
#include "Cell.h"
#include "GameObject.h"
#include "GameDefinitions.h"
#include "Camera.h"
#include "Bat.h"
#include "Bird.h"
#include "Butterfly.h"
#include "SoldierGreen.h"
#include "SoldierYellow.h"
#include "Mummies.h"
#include "Dog.h"
#include "RunningMan.h"
#include "Eaggle.h"
#include "GreenSniper.h"
#include "Ninja.h"
#include "Enemy.h"

#define CELL_WIDTH 128
using namespace std;

class Grid
{
	int mapWidth;
	int stage;
	string cellfilePath;
	string objectfilePath;
	map<int, LPCELL> listCell;
	map<int, LPGAMEOBJECT> listObject;
public:
	Grid(int stage);
	~Grid();
	int CountWords(string str);
	LPGAMEOBJECT CreateObject(int id, int type, int x, int y, int direction, int leftX, int rightX,int distance, int itemtype);//tạo đối tượng
	void LoadListObject();
	void LoadListCell();
	vector<LPGAMEOBJECT> GetListObject();
	void MoveObject(LPGAMEOBJECT x, int xOld, int yOld, int wOld);
	void InsertObject(LPGAMEOBJECT x);
	void ReLoadGrid();
	void TurnOffActive();//tắt active của object ngoài camera
	bool CheckXuatHien(LPGAMEOBJECT obj);//kiểm tra điều kiện để lấy ra khỏi grid
};
#endif // !__GRID_H__