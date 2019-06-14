#include "Grid.h"

Grid::Grid(int stage)
{
	this->stage = stage;
	switch (stage) {
	case 1:
		objectfilePath = "datas\\listobject1.txt";
		cellfilePath = "datas\\listcell1.txt";
		mapWidth = 2048;
		break;
	case 2:
		objectfilePath = "datas\\listobject2.txt";
		cellfilePath = "datas\\listcell2.txt";
		mapWidth = 3072;
		break;
	default:
		break;
	}
	LoadListObject();
	LoadListCell();
}

Grid::~Grid()
{
	listCell.clear();
	listObject.clear();
}

int Grid::CountWords(string str)
{
	stringstream s(str);
	string word;
	int count = 0;
	while (s >> word)
		count++;
	return count;
}

LPGAMEOBJECT Grid::CreateObject(int id, int type, int x, int y, int direction, int leftX, int rightX, int distance,int itemtype)
{
	switch (type)
	{
	case BAT:
		return new Bat(id, type, x, y, direction, leftX, rightX, distance);
	case BIRD:
		return new Bird(id, type, x, y, direction, leftX, rightX, distance);
	case BUTTERFLY:
		return new Butterfly(id, type, x, y, direction, itemtype);
	case DOG:
		return new Dog(id, type, x, y, direction, leftX, rightX, distance);
	case MUMMIES:
		return new Mummies(id, type, x, y, direction, leftX, rightX, distance);
	case SOLDIERGREEN:
		return new SoldierGreen(id, type, x, y, direction, leftX, rightX, distance);
	case SOLDIERYELLOW:
		return new SoldierYellow(id, type, x, y, direction, leftX, rightX, distance);
	case RUNNINGMAN:
		return new RunningMan(id, type, x, y, direction, leftX, rightX, distance);
	case EAGGLE:
		return new Eaggle(id, type, x, y, direction, itemtype);
	case GREENSNIPER:
		return new GreenSniper(id, type, x, y, direction, leftX, rightX, distance);
	default:
		return NULL;
	}
}

void Grid::LoadListObject()
{
	fstream f(objectfilePath);
	int n;
	int id, type, x, y , direction, leftX, rightX, distance,itemtype;
	f >> n;

	for (int i = 0; i < n; i++)
	{
		f >> id >> type >> x >> y >> direction >> leftX >> rightX >> distance>>itemtype;
		this->listObject[id] = CreateObject(id, type, x, y, direction, leftX, rightX, distance,itemtype);
	}
	f.close();
}

void Grid::LoadListCell()
{
	fstream f(cellfilePath);
	string data;
	stringstream stream_data;

	int idc, x, y, ido; //ido là id của object nằm trong cell, idc là id của cell
	int number_of_object_in_cell;
	while (getline(f, data))
	{
		stream_data << data;
		stream_data >> idc;
		//DebugOut(L"id object cua cell %d:  ", idc);
		LPCELL cell = new Cell(idc);

		number_of_object_in_cell = CountWords(data) - 1;
		for (int i = 0; i < number_of_object_in_cell; i++)
		{
			stream_data >> ido;
			//DebugOut(L" %d ", ido);
			cell->AddObject(ido, this->listObject[ido]);
		}
		//DebugOut(L"\n");
		this->listCell[idc] = cell;
		data = "";
		stream_data.clear();
	}

	f.close();
}

vector<LPGAMEOBJECT> Grid::GetListObject()
{
	map<int, LPGAMEOBJECT> mresult;
	vector<LPGAMEOBJECT> listResult;
	mresult.clear();
	listResult.clear();


	int l = (Camera::GetInstance()->GetPosition().x) / CELL_WIDTH;
	int r = ((Camera::GetInstance())->GetPosition().x + GAME_WIDTH) / CELL_WIDTH;

	for (int i = l; i <= r; i++)
	{
		map<int, LPGAMEOBJECT> temp = this->listCell.at(i)->GetListObject();
		for (auto x : temp)
			if (mresult.find(x.second->GetId()) == mresult.end())
			{
				int isAct = x.second->GetActive();
				if ((isAct == 1) || (isAct == 0 && x.second->IsInCamera() && this->CheckXuatHien(x.second)) == true)
				{
					x.second->SetActive(1);
					mresult[x.second->GetId()] = x.second;

				}
			}


	}

	for (auto x : mresult)
		listResult.push_back(x.second);
	return listResult;
}

void Grid::MoveObject(LPGAMEOBJECT x, int xOld, int yOld, int wOld)
{
	int l = xOld / CELL_WIDTH;
	int r = (xOld + wOld) / CELL_WIDTH;
	for (int i = l; i <= r; i++)
		listCell.at(i)->Remove(x->GetId());
	this->InsertObject(x);
}

void Grid::InsertObject(LPGAMEOBJECT x)
{
	int l = x->GetPosition().x / CELL_WIDTH;
	int r = (x->GetPosition().x + x->GetWidth()) / CELL_WIDTH;
	for (int i = l; i <= r; i++)
		listCell.at(i)->AddObject(x->GetId(), x);
}

void Grid::ReLoadGrid()
{
	LoadListObject();
	LoadListCell();
}

void Grid::TurnOffActive()
{
	for (int i = 0; i < mapWidth / 128; i++)
	{
		map<int, LPGAMEOBJECT> objects = listCell.at(i)->GetListObject();
		for (auto x : objects)
			if (x.second->IsInCamera() == false)
			{
				x.second->SetActive(0);
				x.second->SetPosition(x.second->GetInitposition());
			}
	}
}

bool Grid::CheckXuatHien(LPGAMEOBJECT obj)
{
	float ninjaX = Ninja::GetInstance()->GetPosition().x;
	float objX = obj->GetPosition().x;
	if (obj->GetIsContainer()==true)
	{
		if (obj->die == false)
		{
			//obj->die = true;
			return true;
		}
		else return false;

	}
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy->GetDirection() > 0)
	{
		if (ninjaX - objX >= enemy->GetDistance()) return true;
	}
	if (enemy->GetDirection() <= 0)
	{
		if (objX - ninjaX >= enemy->GetDistance()) return true;
	}
	return false;
}
