#include "Stage3.h"
#define MAP_WIDTH 2048
Stage3::Stage3()
{
	this->Select = 1;
	this->time_boss_dead = 0;
	this->ChangeStage(3);
}


Stage3::~Stage3()
{
}


void Stage3::getBrick()
{
	bricks.clear();
	string path = "datas//brick3.txt";
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

void Stage3::Initialize()
{
	sound = Sound::GetInstance();
	if(AllowSound)
	sound->Play(background1, true);
	//Các object được thiết lập tọa độ thế giới thực khi dùng D3DXVECTOR3(x,y,z)
	Camera::GetInstance()->Initialize(0, GAME_HEIGHT);
	//Nhân vật ninja
	ninja = Ninja::GetInstance();
	ninja->DecreaseHP(-20);
	ninja->SetPosition(D3DXVECTOR3(100, 60, 0));
	getBrick();

	boss = new Boss();
	//Nền game (thêm vào cho dễ nhìn :D)
	back = new Background(3);
	Time::GetInstance()->Reset();
	Items::GetInstance()->Clear();
}

void Stage3::DestroyAll()
{

}

void Stage3::Update(DWORD dt)
{

	//ninja chưa chết mới cho pause game
	if (IsKeyPress(DIK_P) && IsNinjaDie == false && Time::GetInstance()->GetTime() > 0)
		IsGamePause = !IsGamePause;

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
		

	//ninja chết mà vẫn còn mạng
	if (ninja->die == true && time_render_dead>1500 && ninja->GetLife() > 0)
		SetNinjaAfterDie();

	if (ninja->die == false)
	{
		if (sound->isPlaying(background1) == false && AllowSound) sound->Play(background1, true);
		//danh sách object có thể va chạm với ninja
		vector<LPGAMEOBJECT> Coobjects;
		Coobjects.clear();

		//push bricks and enemies
#pragma region push bricks and enemies
		for (int i = 0; i < bricks.size(); i++)
			Coobjects.push_back(bricks[i]);

		if (boss->die == false)
		{
			Coobjects.push_back(boss);

			vector<Bullet*> listBullet;
			listBullet = boss->getBullets(); //đưa 3 viên đạn (nếu có) của boss vào xét va chạm
			for (auto x : listBullet)
				Coobjects.push_back(x);
		}
#pragma endregion

		ninja->Update(dt, &Coobjects);

		//VA CHẠM CHO QUÁI
		//************************************************************
	
		back->Update(dt); //update vị trí background
		boss->Update(dt, &bricks);

		Time::GetInstance()->Update(dt); //đếm thời gian cho game

		if (boss->getHP() <= 0)
		{
			boss->die = true;
			time_boss_dead += dt;
		}
	}

	if (ninja->die == true && time_render_dead > 1500 && ninja->GetLife() <= 0)
		this->ProcessGameOver(dt);

	if (boss->die == true && ninja->die == false && Time::GetInstance()->GetTime()>0)
	{
		ninja->SetIsBossDie(true);
		Time::GetInstance()->Pause();
		ninja->IncreaseScore(100);
		Time::GetInstance()->SetTime(Time::GetInstance()->GetTime() - 1);
	}

	if (boss->die == true && ninja->die == false && time_boss_dead >= TIME_EXPLOSION && Time::GetInstance()->GetTime() == 0)
		this->ProcessGameWin(dt);
}

void Stage3::Render()
{

	//nếu ninja chưa chết vẫn render bình thường
	if (ninja->die == false)
	{
		back->Draw();
		ninja->Render();
		boss->Render();
		for (auto x : bricks) x->Render();



		LPSPRITE spblack = Sprites::GetInstance()->Get(370);
		spblack->RenderNotTransForm(0, 0);

		Explosion::GetInstance()->Render(); //render nổ nếu đang xảy ra

		this->RenderScoreboard(); //vẽ bảng điểm

		if (IsGamePause)
		{
			wsprintfW(buffer, L"RESUME");
			Graphic::GetInstance()->DrawMessage1(107, 100, 320, 240, D3DCOLOR_XRGB(255, 0, 255), buffer);
		}
	}


	//nếu boss chết và ninja còn sống(gamewin), cần thêm điều kiện boss nổ xong mới render
	if (boss->die == true && ninja->die == false && time_boss_dead >= TIME_EXPLOSION && Time::GetInstance()->GetTime() == 0)
		this->RenderGameWin();

	if (ninja->die == true && time_render_dead <= 1500)
	{
		boss->Render();

		ninja->Render();

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
	if (ninja->die == true && time_render_dead > 1500 && ninja->GetLife() <= 0 && boss->die==false)
		this->RenderGameOver();

}

void Stage3::RenderGameOver()
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

void Stage3::RenderGameWin()
{
	LPSPRITE gamewin = Sprites::GetInstance()->Get(380);
	gamewin->RenderNotTransForm(0, 0);

	wsprintfW(buffer, L"GAMEWIN");
	Graphic::GetInstance()->DrawMessage1(90, 50, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"YOUR SCORE: %d",ninja->getScore());
	Graphic::GetInstance()->DrawMessage1(50, 70, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"EXIT");
	Graphic::GetInstance()->DrawMessage1(110, 120, 320, 240, D3DCOLOR_XRGB(255, 0, 255), buffer);
	wsprintfW(buffer, L"Ninja Gaiden Game by KDH Tech.");
	Graphic::GetInstance()->DrawMessage1(15, 150, 320, 240, D3DCOLOR_XRGB(155, 233, 255), buffer);
}

void Stage3::ProcessGameOver(DWORD dt)
{
	if (ninja->die == true && ninja->GetLife() <= 0)
	{
		Sound::GetInstance()->StopAll();

		if (IsKeyPress(DIK_DOWN) || IsKeyPress(DIK_UP)) this->Select = -this->Select;

		if (IsKeyDown(DIK_RETURN) && this->Select == END)
		{
			DestroyWindow(hwndGlobal);
			exit(WM_CLOSE);
		}
		if (IsKeyDown(DIK_RETURN) && this->Select == CONTINUE)
		{
			IsNinjaDie = false;
			if(AllowSound)
			sound->Play(background1, true);
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
		}
	}
}

void Stage3::ProcessGameWin(DWORD dt)
{
	if (boss->die == true && IsKeyDown(DIK_RETURN))
	{
		DestroyWindow(hwndGlobal);
		exit(WM_CLOSE);
	}
}

void Stage3::RenderScoreboard()
{
	wsprintfW(buffer, L"Stage: 3-3 ");
	Graphic::GetInstance()->DrawMessage1(130, 2, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"Ninja:");
	Graphic::GetInstance()->DrawMessage1(130, 17, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	wsprintfW(buffer, L"Enemy:");
	Graphic::GetInstance()->DrawMessage1(130, 32, 320, 240, D3DCOLOR_XRGB(255, 255, 255), buffer);
	int blood = ninja->getHP();
	if (blood > 16) blood = 16;
	LPWSTR HPNinja[] = { L"",L"I",L"II",L"III",L"IIII",L"IIIII",L"IIIIII",L"IIIIIII",L"IIIIIIII",L"IIIIIIIII",L"IIIIIIIIII",L"IIIIIIIIIII",L"IIIIIIIIIIII",L"IIIIIIIIIIIII",L"IIIIIIIIIIIIII",L"IIIIIIIIIIIIIII",L"IIIIIIIIIIIIIIII" };
	wsprintfW(buffer, HPNinja[blood]);
	Graphic::GetInstance()->DrawMessage1(188, 17, 320, 240, D3DCOLOR_XRGB(255, 0, 127), buffer);
	blood = boss->getHP();
	if (blood > 16) blood = 16;
	wsprintfW(buffer, HPNinja[blood]);
	Graphic::GetInstance()->DrawMessage1(188, 32, 320, 240, D3DCOLOR_XRGB(255, 0, 127), buffer);

	
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

