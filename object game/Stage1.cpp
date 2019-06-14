#include "Stage1.h"
#define MAP_WIDTH 2048
Stage1::Stage1()
{
	Select = 1;
	this->ChangeStage(1);
}


Stage1::~Stage1()
{

}


void Stage1::getBrick()
{
	bricks.clear();
	string path = "datas//brick1.txt";
	fstream fs(path.c_str());
	int numObj;
	fs >> numObj;

	for (int i = 0; i < numObj; i++)
	{
		int l, t, r, b;
		fs >> l >> t >> r >> b;
		Brick *brick = new Brick(l, t, r, b);
		bricks.push_back(brick);
	}
	fs.close();
}

void Stage1::Initialize()
{
#pragma region play nhạc nền map 1
	sound = Sound::GetInstance();
	if(AllowSound)
	sound->Play(background1, true);
#pragma endregion

	//Các object được thiết lập tọa độ thế giới thực khi dùng D3DXVECTOR3(x,y,z)
	Camera::GetInstance()->Initialize(0, GAME_HEIGHT);

#pragma region Lấy instance Ninja +add animation

	ninja = Ninja::GetInstance();
	ninja->SetPosition(D3DXVECTOR3(NINJA_POSITION_MAP1_X, NINJA_POSITION_MAP1_Y, 0));
	
#pragma endregion

	getBrick();
	back = new Background(1);
	grid = new Grid(1);
	Time::GetInstance()->Reset();
	Items::GetInstance()->Clear();
}

void Stage1::DestroyAll()
{
	
}

void Stage1::Update(DWORD dt)
{
	//ninja chưa chết mới cho pause game
	if (IsKeyPress(DIK_P) && IsNinjaDie == false) IsGamePause = !IsGamePause;
	if (IsGamePause)
	{
		sound->StopAll();
		return;
	}

	if (ninja->die == true && time_render_dead <= 1500)
	{
		time_render_dead += dt;
		ninja->SetState(DIE);
	}
		

	if (ninja->die == false)
	{
		if (sound->isPlaying(background1) == false && AllowSound) sound->Play(background1, true);
		//chuyển màn chơi
		if (ninja->GetPosition().x >= MAP_WIDTH_1 - 30)
		{
			Sound::GetInstance()->Stop(background1);
			this->ChangeStage(2);
			return;
		}
		vector<Item*> items = Items::GetInstance()->GetAllItems();
		for (auto x : items)
			x->Update(dt, &bricks);


		//Tạo danh sách object có thể đụng độ với ninja
		vector<LPGAMEOBJECT> Coobjects;
		Coobjects.clear();

#pragma region push bricks and enemies
		for (int i = 0; i < bricks.size(); i++)
			Coobjects.push_back(bricks[i]);

		grid->TurnOffActive();

		enemies.clear();
		enemies = grid->GetListObject();

		for (int i = 0; i < enemies.size(); i++)
			Coobjects.push_back(enemies[i]);
#pragma endregion


		ninja->Update(dt, &Coobjects); //truyền Coobjects vào update ninja để xét đụng độ
		Coobjects.clear();

#pragma region update & va chạm cho quái

		if (ninja->isStillStopGame() == 0)
			for (auto x : enemies)
			{
				int xOld = x->GetPosition().x;
				int yOld = x->GetPosition().y;
				int widthOld = x->GetWidth();
				x->Update(dt, &bricks);
				grid->MoveObject(x, xOld, yOld, widthOld);
			}
#pragma endregion




		//Nhân vật chạy đến giữa màn hình mới bắt đầu dịch chuyển camera
		if (ninja->GetPosition().x >= GAME_WIDTH / 2 && ninja->GetPosition().x <= MAP_WIDTH - GAME_WIDTH / 2)
		{
			Camera::GetInstance()->Update(ninja->GetPosition());
		}

		back->Update(dt);

		Time::GetInstance()->Update(dt);
	}


	if (ninja->die == true && time_render_dead > 1500 && ninja->GetLife() > 0)
		SetNinjaAfterDie();

	if (ninja->die == true && time_render_dead > 1500 && ninja->GetLife() <= 0)
		this->ProcessGameOver(dt);
	
}

void Stage1::Render()
{
	
	if (!ninja->die)
	{
		vector<Item*> items = Items::GetInstance()->GetAllItems();

		back->Draw();
		ninja->Render();

		for (auto x : bricks) x->Render();

		enemies.clear();
		enemies = grid->GetListObject();

		for (auto x : enemies)
			x->Render();

		Explosion::GetInstance()->Render();
		for (auto x : items)
			x->Render();

		this->RenderScoreboard();

		if (IsGamePause)
		{
			wsprintfW(buffer, L"RESUME");
			Graphic::GetInstance()->DrawMessage1(107, 100, 320, 240, D3DCOLOR_XRGB(255, 0, 255), buffer);
		}
	}
	
	if (ninja->die == true && time_render_dead <= 1500)
	{
		enemies.clear();
		enemies = grid->GetListObject();
		
		ninja->Render();
		for (auto x : enemies)
			x->Render();
		switch (select_alpha)
		{
		case 0:
			back->Draw(150);
			select_alpha++;
			break;
		case 1:
			back->Draw(179);
			select_alpha++;
			break;
		case 2:
			back->Draw(110);
			select_alpha++;
			break;
		case 3:
			back->Draw(190);
			select_alpha = 0;
		default:
			break;
		}
	}
	if (ninja->die == true && time_render_dead > 1500 && ninja->GetLife() <= 0)
		this->RenderGameOver();
}

void Stage1::RenderGameOver()
{
	LPSPRITE gameover = Sprites::GetInstance()->Get(380);
	gameover->RenderNotTransForm(0, 0);

	switch (this->Select)
	{
	case CONTINUE:
		wsprintfW(buffer, L"GAMEOVER");
		Graphic::GetInstance()->DrawMessage1(90, 50, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
		wsprintfW(buffer, L"CONTINUE");
		Graphic::GetInstance()->DrawMessage1(93, 90, 320, 240, D3DCOLOR_XRGB(255, 0, 255), buffer);
		wsprintfW(buffer, L"END");
		Graphic::GetInstance()->DrawMessage1(115, 120, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
		break;
	case END:
		wsprintfW(buffer, L"GAMEOVER");
		Graphic::GetInstance()->DrawMessage1(90, 50, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
		wsprintfW(buffer, L"CONTINUE");
		Graphic::GetInstance()->DrawMessage1(93, 90, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
		wsprintfW(buffer, L"END");
		Graphic::GetInstance()->DrawMessage1(115, 120, 320, 240, D3DCOLOR_XRGB(255, 0, 255), buffer);
		break;
	default:
		break;
	}
}

void Stage1::ProcessGameOver(DWORD dt)
{
		sound->StopAll();

		
		if (IsKeyPress(DIK_DOWN) || IsKeyPress(DIK_UP)) this->Select = -this->Select;

		if (IsKeyDown(DIK_RETURN) && this->Select == END)
		{
			DestroyWindow(hwndGlobal);
			exit(WM_CLOSE);
		}
		if (IsKeyDown(DIK_RETURN) && this->Select == CONTINUE)
		{
			IsNinjaDie = false;
			Time::GetInstance()->Reset();
			ninja->IncreaseScore(-ninja->getScore());
			ninja->SetState(IDLE);
			ninja->SetDirection(1);
			ninja->DecreaseHP(-17);
			ninja->die = false;
			ninja->SetLife(2);
			ninja->SetStrength(0);
			ninja->SetPosition(D3DXVECTOR3(40, 60, 0));
			Camera::GetInstance()->Initialize(0, GAME_HEIGHT);
			Items::GetInstance()->Clear();
			if(AllowSound)
			sound->Play(background1, true);
			grid->ReLoadGrid();
		}
}

void Stage1::RenderScoreboard()
{
	//Cột bên trái
	wsprintfW(buffer, L"Stage: 3-1 ");
	Graphic::GetInstance()->DrawMessage1(132, 2, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"Ninja:");
	Graphic::GetInstance()->DrawMessage1(132, 17, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"IIIIIIIIIIIIIIII ");
	Graphic::GetInstance()->DrawMessage1(184, 32, 320, 240, D3DCOLOR_XRGB(255, 0, 127), buffer);
	int blood = ninja->getHP();
	if (blood > 16) blood = 16;
	LPWSTR HPNinja[] = { L"",L"I",L"II",L"III",L"IIII",L"IIIII",L"IIIIII",L"IIIIIII",L"IIIIIIII",L"IIIIIIIII",L"IIIIIIIIII",L"IIIIIIIIIII",L"IIIIIIIIIIII",L"IIIIIIIIIIIII",L"IIIIIIIIIIIIII",L"IIIIIIIIIIIIIII",L"IIIIIIIIIIIIIIII" };
	wsprintfW(buffer, HPNinja[blood]);
	Graphic::GetInstance()->DrawMessage1(184, 17, 320, 240, D3DCOLOR_XRGB(255, 0, 127), buffer);


	wsprintfW(buffer, L"Enemy:");
	Graphic::GetInstance()->DrawMessage1(132, 32, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	//Cột bên phải

	wsprintfW(buffer, L"Score: ");
	Graphic::GetInstance()->DrawMessage1(5, 2, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"Timer: ");
	Graphic::GetInstance()->DrawMessage1(5, 17, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"Life: %d", ninja->GetLife());
	Graphic::GetInstance()->DrawMessage1(5, 32, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);

	wsprintfW(buffer, L"%d", Time::GetInstance()->GetTime());
	Graphic::GetInstance()->DrawMessage1(60, 17, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"%d", Ninja::GetInstance()->getScore());
	Graphic::GetInstance()->DrawMessage1(60, 2, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);

	wsprintfW(buffer, L"- %d", Ninja::GetInstance()->GetStrength());
	Graphic::GetInstance()->DrawMessage1(80, 33, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);

	LPSPRITE sp = Sprites::GetInstance()->Get(360);
	sp->RenderNotTransForm(104, 28);

	LPSPRITE spstrength = Sprites::GetInstance()->Get(390);
	spstrength->RenderNotTransForm(55, 33);

	if (ninja->GetNowWeapon() == I_THROWINGSTAR)
	{
		LPSPRITE sp2 = Sprites::GetInstance()->Get(310);
		sp2->RenderNotTransForm(106, 32);
	}
	if (ninja->GetNowWeapon() == I_WINDMILLSTAR)
	{
		LPSPRITE sp2 = Sprites::GetInstance()->Get(320);
		sp2->RenderNotTransForm(106, 32);
	}
}
