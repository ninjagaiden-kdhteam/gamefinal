#include "Game.h"



Game * Game::__instance = NULL;

Game * Game::GetInstance()
{
	if (__instance == NULL) __instance = new Game();
	return __instance;
}

void Game::Initialize(HWND hWnd, int, int)
{
	input = Input::GetInstance();
	input->InitDirectInput();
	input->InitKeyboard(hWnd);
	Graphic::GetInstance()->Initialize(hWnd);
	LoadResources();
	stageManager = new StageManager();
	stageManager->Initialize(hWnd);
	stageManager->LoadStage(1);
}

void Game::LoadResources()
{
	textures = Textures::GetInstance();
	textures->Add(0, L"textures\\ninja.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(1, L"textures\\tileBackGround1.png", 0);
	textures->Add(2, L"textures\\tileBackGround2.png", 0);
	textures->Add(3, L"textures\\tileBackGround3.png", 0);
	textures->Add(4, L"textures\\EnemiesAndBosses.png", 0);
	textures->Add(5, L"textures\\ItemsandContainers.png", 0);
	textures->Add(6, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(7, L"textures\\ItemsandContainers2.png", 0);
	textures->Add(8, L"textures\\Board.png", 0);
	textures->Add(9, L"textures\\blackboard.png", 0);
	textures->Add(10, L"textures\\strength.png", 0);
	sprites = Sprites::GetInstance();
	animations = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texNinja = textures->Get(0);
	LPDIRECT3DTEXTURE9 texEninems = textures->Get(4);
	LPDIRECT3DTEXTURE9 texItems = textures->Get(5);
	LPDIRECT3DTEXTURE9 texItems2 = textures->Get(7);
	LPDIRECT3DTEXTURE9 board = textures->Get(8);
	LPDIRECT3DTEXTURE9 blackboard = textures->Get(9);
	LPDIRECT3DTEXTURE9 strength = textures->Get(10);
#pragma region create_Sprites_from_texture_for_ninja 
#pragma region idle
	sprites->Add(00000, 3, 5, 3 + 17, 5 + 32, texNinja, 0, 0);
#pragma endregion
#pragma region run
	sprites->Add(00010, 339, 6, 339 + 20, 6 + 31, texNinja, 0, 0);
	sprites->Add(00011, 368, 6, 368 + 20, 6 + 31, texNinja, 0, 0);
	sprites->Add(00012, 400, 6, 400 + 20, 6 + 31, texNinja, 0, 0);
#pragma endregion
#pragma region sit
	sprites->Add(00020, 3, 52, 3 + 17, 52 + 24, texNinja, 0, -8);
#pragma endregion
#pragma region attack
	sprites->Add(00030, 42, 6, 42 + 22, 6 + 32, texNinja, -1, -1);
	sprites->Add(00031, 66, 8, 66 + 22, 8 + 32, texNinja, -7, -3);
	sprites->Add(00032, 111, 8, 111 + 22, 8 + 32, texNinja, -4, -3);
#pragma endregion
#pragma region sit attack
	sprites->Add(00040, 35, 53, 35 + 20, 53 + 25, texNinja, 0, -9);
	sprites->Add(00041, 58, 53, 58 + 20, 53 + 25, texNinja, -4, -9);
	sprites->Add(00042, 100, 53, 100 + 20, 53 + 25, texNinja, -4, -9);
#pragma endregion
#pragma region jump
	sprites->Add(00050, 142, 53, 142 + 16, 53 + 22, texNinja, 0, 0);
	sprites->Add(00051, 166, 55, 166 + 22, 55 + 16, texNinja, 0, 0);
	sprites->Add(00052, 194, 53, 194 + 16, 53 + 22, texNinja, 0, 0);
	sprites->Add(00053, 217, 55, 217 + 22, 55 + 16, texNinja, 0, 0);
#pragma endregion
#pragma region latch+climb
	sprites->Add(00060, 267, 6, 267 + 16, 6 + 31, texNinja, 0, 0);
	sprites->Add(00061, 289, 6, 289 + 16, 9 + 29, texNinja, 0, 0);
#pragma endregion //bám và leo

#pragma region use item
	sprites->Add(00070, 164,6,164+18,6+31, texNinja, -2, -1);
	sprites->Add(00071, 189,8,198+26,8+29, texNinja, -17,-3);
	sprites->Add(00072, 227,8,227+26,8+29, texNinja, -17, -3);
#pragma endregion
#pragma endregion



#pragma region Add sprites to Animations
	LPANIMATION ani;
#pragma region idle
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00000);
	animations->Add(0, ani);
#pragma endregion
#pragma region run
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00010);
	ani->AddFrame(00011);
	ani->AddFrame(00012);
	animations->Add(1, ani);
#pragma endregion
#pragma region sit
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00020);
	animations->Add(2, ani);
#pragma endregion
#pragma region attack
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00030);
	ani->AddFrame(00031);
	ani->AddFrame(00032);
	animations->Add(3, ani);
#pragma endregion
#pragma region sit attack
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00040);
	ani->AddFrame(00041);
	ani->AddFrame(00042);
	animations->Add(4, ani);
#pragma endregion
#pragma region jump
	ani = new Animation(100);
	ani->AddFrame(00050);
	ani->AddFrame(00051);
	ani->AddFrame(00052);
	ani->AddFrame(00053);

	animations->Add(5, ani);
#pragma endregion
#pragma region latch
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00060);
	animations->Add(6, ani);
#pragma endregion
#pragma region climb
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00060);
	ani->AddFrame(00061);
	animations->Add(7, ani);
#pragma endregion
#pragma region being attacked
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00050);
	animations->Add(8, ani);
#pragma endregion
#pragma region use item
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00070);
	ani->AddFrame(00071);
	ani->AddFrame(00072);
	animations->Add(9, ani);
#pragma endregion
#pragma region ninja die
	ani = new Animation(NINJA_ANIMATION_TIME);
	ani->AddFrame(00050);
	animations->Add(10, ani);
#pragma endregion
#pragma endregion

#pragma region linh vàng
	sprites->Add(00100, 216, 52, 240, 92, texEninems, 0, 0);
	sprites->Add(00101, 245, 52, 269, 92, texEninems, 0, 0);
	sprites->Add(00102, 282, 52, 282 + 16, 52 + 40, texEninems, 8, 0);
	ani = new Animation(210);
	ani->AddFrame(00100);
	ani->AddFrame(00101);
	ani->AddFrame(00102);
	animations->Add(20, ani);

#pragma endregion
#pragma region Bat
	sprites->Add(00120, 107, 11, 107 + 16, 11 + 13, texEninems, 0, 0);
	sprites->Add(00121, 127, 14, 127 + 15, 14 + 13, texEninems, 0, -7);
	ani = new Animation(100);
	ani->AddFrame(00120);
	ani->AddFrame(00121);
	animations->Add(30, ani);
#pragma endregion
#pragma region Dog
	sprites->Add(00130, 314, 79, 314 + 31, 79 + 14, texEninems, 0, 0);
	sprites->Add(00131, 355, 78, 355 + 24, 78 + 15, texEninems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(00130);
	ani->AddFrame(00131);
	animations->Add(40, ani);
#pragma endregion
#pragma region Bird
	sprites->Add(00140, 478, 74, 478 + 16, 74 + 16, texEninems, 0, 0);
	sprites->Add(00141, 505, 59, 505 + 17, 59 + 25, texEninems, 0, 14);
	ani = new Animation(100);
	ani->AddFrame(00140);
	ani->AddFrame(00141);
	animations->Add(50, ani);
#pragma endregion
#pragma region Butterfly
	sprites->Add(00150, 80, 55, 80 + 16, 55 + 16, texItems, 0, 0);
	sprites->Add(00151, 95, 50, 95 + 16, 50 + 16, texItems, 0, 3);
	ani = new Animation(100);
	ani->AddFrame(00150);
	ani->AddFrame(00151);
	animations->Add(60, ani);
#pragma endregion
#pragma region Soldier xanh
	sprites->Add(00160, 58, 60, 58 + 15, 60 + 32, texEninems, 0, 0);
	sprites->Add(00161, 83, 60, 83 + 16, 60 + 32, texEninems, 0, 0);
	sprites->Add(00162, 133, 60, 133 + 24, 60 + 32, texEninems, -8, 0);
	sprites->Add(00163, 164, 60, 164 + 20, 60 + 32, texEninems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(00160);
	ani->AddFrame(00161);
	animations->Add(70, ani);
	ani = new Animation(100);
	ani->AddFrame(00162);
	animations->Add(71, ani);

#pragma endregion
#pragma region Mummies
	sprites->Add(00170, 413, 14, 413 + 24, 14 + 32, texEninems, 0, 0);
	sprites->Add(00171, 449, 14, 449 + 24, 14 + 32, texEninems, 0, 0);
	sprites->Add(00172, 496, 3, 496 + 16, 3 + 43, texEninems, 0, 11);
	ani = new Animation(600);
	ani->AddFrame(00170);
	ani->AddFrame(00171);
	animations->Add(80, ani);
	ani = new Animation(600);
	ani->AddFrame(00172);
	animations->Add(81,ani);
#pragma endregion
#pragma region Sword
	sprites->Add(180, 140, 24, 140, 24, texItems, 0, 0);
	sprites->Add(181, 151, 34, 151 + 16, 34 + 7, texItems, 0, 0);
	sprites->Add(182, 173, 36, 173 + 11, 36 + 5, texItems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(180);
	ani->AddFrame(181);
	ani->AddFrame(182);
	animations->Add(90, ani);
#pragma endregion
#pragma region Bullet
	sprites->Add(190, 196, 69, 196 + 8, 69 + 3, texEninems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(190);
	animations->Add(100, ani);

	sprites->Add(191, 443,273,443+5,273+5, texEninems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(191);
	animations->Add(101, ani);
#pragma endregion
#pragma region GreenSniper
	sprites->Add(200, 390, 68, 390+24, 68+25, texEninems, 0, 0);
	sprites->Add(201, 420, 68, 420+24, 68+25, texEninems, 0, 0);
	sprites->Add(202, 420, 64, 420 + 36, 64 + 29, texEninems, -11, 4);
	ani = new Animation(100);
	ani->AddFrame(200);
	ani->AddFrame(201);
	animations->Add(110, ani);
	ani = new Animation(100);
	ani->AddFrame(202);

	animations->Add(111, ani);
#pragma endregion
#pragma region RunningMan
	sprites->Add(210, 3, 60, 3+16, 60+32, texEninems, 0, 0);
	sprites->Add(211, 24, 60, 24+16, 60+32, texEninems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(210);
	ani->AddFrame(211);
	animations->Add(120, ani);
#pragma endregion
#pragma region Eaggle
	sprites->Add(220, 118, 51, 118+16, 51 + 15, texItems, 0, 0);
	sprites->Add(221, 139, 53, 139+16, 53 + 15, texItems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(220);
	ani->AddFrame(221);
	animations->Add(130, ani);
#pragma endregion
#pragma region explode
	sprites->Add(230, 369,44,369+24,44+32, texItems, -20, 0);
	sprites->Add(231, 319, 1, 319+30,1+38, texItems, -20, 0);
	ani = new Animation(100);
	ani->AddFrame(230);
	ani->AddFrame(230);
	ani->AddFrame(231);
	animations->Add(140, ani);
#pragma endregion

#pragma region Throwing star
	sprites->Add(240, 33,32,33+8,32+7, texItems2, 0, 0);
	sprites->Add(241,48,32,48+8,32+7, texItems2, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(240);
	ani->AddFrame(241);
	animations->Add(150, ani);
#pragma endregion

#pragma region Windmill star
	sprites->Add(250, 29,90,29+16,90+16, texItems2, 0, 0);
	sprites->Add(251, 50, 90,50 + 16, 90 + 16, texItems2, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(250);
	ani->AddFrame(251);
	animations->Add(160, ani);
#pragma endregion
#pragma region Knife
	sprites->Add(260, 526, 9, 526+8, 9+15, texEninems, 0, 0);
	sprites->Add(261, 496,3,496+8,3+15, texEninems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(260);
	ani->AddFrame(261);
	animations->Add(170, ani);
#pragma endregion

#pragma region bonus Point item
	sprites->Add(270,46,3,46+16,3+15 , texItems2, 0, 0); //blue
	sprites->Add(271,67,3,67+16,3+15, texItems2, 0, 0); //red
	ani = new Animation(100);
	ani->AddFrame(270);
	animations->Add(180, ani);//blue

	ani = new Animation(100);
	ani->AddFrame(271);
	animations->Add(181, ani);//red
	
#pragma endregion

#pragma region Spirit points item
	sprites->Add(280, 7,3,7+15,3+15, texItems2, 0, 0); //blue
	sprites->Add(281,27,3,+27+15,3+15, texItems2, 0, 0); //red
	ani = new Animation(100);
	ani->AddFrame(280);
	animations->Add(190, ani);//blue

	ani = new Animation(100);
	ani->AddFrame(281);
	animations->Add(191, ani);//red
	
#pragma endregion

#pragma region Time Freeze item
	sprites->Add(290, 106,3,106+12,3+15, texItems2, 0, 0); 
	ani = new Animation(100);
	ani->AddFrame(290);
	animations->Add(200, ani);
#pragma endregion

#pragma region Health item
	sprites->Add(300,89,2,89+12,2+16, texItems2, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(300);
	animations->Add(210, ani);
#pragma endregion

#pragma region Throwing star item
	sprites->Add(310, 7,27,7+16,27+16, texItems2, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(310);
	animations->Add(220, ani);
#pragma endregion

#pragma region Windmill star item
	sprites->Add(320, 7,90,7+16,90+16, texItems2, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(320);
	animations->Add(230, ani);
#pragma endregion

#pragma region Flames item
	sprites->Add(330, 7,69,7+16,69+16, texItems2, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(330);
	animations->Add(240, ani);
#pragma endregion

#pragma region Boss
	sprites->Add(340, 354, 253, 354 + 34, 253 + 48, texEninems, 0, 0);
	sprites->Add(341, 398, 247, 398 + 38, 247 + 54, texEninems, 0, 0);
	ani = new Animation(100);
	ani->AddFrame(340);
	animations->Add(250, ani);

	ani = new Animation(100);
	ani->AddFrame(341);
	animations->Add(251, ani);
#pragma endregion

#pragma region Boss die
	//sprites->Add(350,358,94,358+16,94+16, texNinja, 0, 0);
	sprites->Add(350, 351, 86, 351 + 32, 86 + 32, texNinja, 0, 0);
	sprites->Add(351,384,85,384+32,85+32, texNinja, 0, 0);

	ani = new Animation(100);
	ani->AddFrame(350);
	ani->AddFrame(351);
	animations->Add(260, ani);
#pragma endregion
#pragma region khung chua icon cua item
	sprites->Add(360, 0, 0,22,23, board, 0, 0);
#pragma endregion
#pragma region blackboard map3
	sprites->Add(370, 0, 0, 260, 48, blackboard, 0, 0);
#pragma endregion
#pragma region gameover, gamewin
	sprites->Add(380, 0, 0, 260, 215, blackboard, 0, 0);
#pragma endregion
#pragma region strength icon
	sprites->Add(390, 0, 0, 19, 18, strength, 0, 0);
#pragma endregion
}

void Game::Run()
{
	Render();
}

void Game::Update(DWORD dt)
{
	input->PollKeyboard();

	stageManager->Update(dt);
	if (IsKeyPress(DIK_M)) AllowSound = !AllowSound;
	if (!AllowSound) Sound::GetInstance()->StopAll();
}

void Game::Render()
{
	stageManager->Render();
}

Game::~Game()
{
	input->KillKeyboard();
}