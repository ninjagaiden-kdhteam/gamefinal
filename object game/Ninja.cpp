#include "Ninja.h"

Ninja* Ninja::__Instance = NULL;

Ninja* Ninja::GetInstance()
{
	if (__Instance == NULL) __Instance = new Ninja();
	return __Instance;
}

Ninja::Ninja() :GameObject::GameObject()
{
	//add animation
	for (int i = 0; i < 11; i++)
		this->AddAnimation(i);

#pragma region khởi tạo thuộc tính
	isHitting = 0;
	isJumping = 0;
	isSitting = 0;
	isClimbing = 0;
	isLatching = 0;
	isJumpWall = 0;
	isUsingItem = 0;
	canLatch = 0;

	minClimb = 0;
	maxClimb = 0;
	canClimb = 0;
	isBeingAttacked = 0;
	unTouchable = 0;
	unTouchable_start = 0;
	flicker = 0;

	HP = 16;
	score = 0;
	Life = 2;
	strength = 0;
	createStar = 0;
	godMode = 0;
#pragma endregion


	//tạo mảng weapons
	weapons.clear();
	LPWEAPON w1 = new Sword(); //không được sử dụng
	w1->SetActive(0);
	LPWEAPON w2 = new ThrowingStar();
	w2->SetActive(0);
	LPWEAPON w3 = new WindmillStar();
	w3->SetActive(0);
	weapons.push_back(w1);
	weapons.push_back(w2);
	weapons.push_back(w3);

	nowWeapon = NULL;// = weapons[2];//weapons[1]: throwing,weapons[2]: windmill

	ninjaSword = new Sword(position.x, position.y, direction);
}

//check có đang dừng game do item ngưng thời gian không
int Ninja::isStillStopGame()
{
	if (IsTimeFreeze && GetTickCount() - start_stop <= STOP_GAME_TIME)
		return 1;
	start_stop = 0;
	IsTimeFreeze=false;
	Time::GetInstance()->UnPause();
	return 0;
}
//check có đang còn untouch không
int Ninja::stillUntouchable()
{
	if (GetTickCount() - unTouchable_start >= NINJA_UNTOUCHABLE_TIME)
	{
		endUntouchable();
		return 0;
	}
	return 1;
}
//get type của weapon hiện tại đang dùng, dùng cho vẽ scoreboard
EItem Ninja::GetNowWeapon()
{
	if (nowWeapon != NULL)
	{
		if (nowWeapon->GetType() == THROWINGSTAR) return I_THROWINGSTAR;
		if (nowWeapon->GetType() == WINDMILLSTAR) return I_WINDMILLSTAR;
	}
}

void Ninja::SetLife(int life)
{
	this->Life = life;
}

//va chạm với gạch
void Ninja::collisionBrick(vector<LPGAMEOBJECT> *coObjects, int coWall)
{
	vector<LPCOLLISIONEVENT> coEvents; //lưu danh sách cái object có thể va chạm trong frame tới
	vector<LPCOLLISIONEVENT> coEventsResult;//lưu danh sách 2 object gần nhất sẽ va chạm, theo trục x, y

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents); //tính toán coEvents

	if (coEvents.size() == 0) //không có va chạm
	{
		position.x += dx;
		position.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		position.x += min_tx*dx + nx*0.2f;

		if (ny < 0) //nếu va chạm gạch dưới
			position.y += min_ty*dy - ny*0.2f;
		else //nếu va chạm gạch trên (không xét)
			position.y += dy;
		
		if (nx != 0) vx = 0; 
		if (ny < 0)
		{
			vy = 0; 
			isJumping = 0;
			isBeingAttacked = 0;
		}
	}	

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

//check ninja có trên mặt đất không
int Ninja::isOnGround(vector<LPGAMEOBJECT> *bricks)
{
	vector<LPCOLLISIONEVENT> coEvents; //lưu danh sách cái object có thể va chạm trong frame tới
	vector<LPCOLLISIONEVENT> coEventsResult;//lưu danh sách 2 object gần nhất sẽ va chạm, theo trục x, y

	coEvents.clear();
	CalcPotentialCollisions(bricks, coEvents);//tính toán coEvents

	if (coEvents.size() == 0) //không có va chạm
	{
		return 0;
	}

	float min_tx, min_ty, nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (nx == 0) return 0; //không có va chạm
	return 1;
}

int Ninja::collisionWall(vector<LPGAMEOBJECT> *coObjects)
{
	int iscol = 0; //kiểm tra có va chạm với wall ko
	vector<LPCOLLISIONEVENT> coEvents; //lưu danh sách cái object có thể va chạm trong frame tới
	vector<LPCOLLISIONEVENT> coEventsResult;//lưu danh sách 2 object gần nhất sẽ va chạm, theo trục x, y
	
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);//không có va chạm

	if (coEvents.size() == 0) //không có va chạm
	{
		return 0;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//có va chạm theo chiều x
		if (nx != 0)
		{
			// lấy giới hạn bám wall
			for (int i = 0; i<coEventsResult.size(); i++)
				if (coEventsResult[i]->nx != 0)
				{		
					Wall *wall = dynamic_cast<Wall *>(coEventsResult[i]->obj);
					minClimb = wall->getMinClimb();
					maxClimb = wall->getMaxClimb();
					canClimb = wall->getCanClimb();		
				}

			
			position.x += min_tx*dx + nx*0.2f;
			vx = 0;
			//nếu trong giới hạn bám tường
			if (position.y <= maxClimb && position.y-32 >= minClimb) //32 là chiều cao ninja
			{
				iscol = 1;
				canLatch = 1; //bật cờ canLatch, để keyUpdate sang trạng thái latch
				if (isBeingAttacked == 1) //nếu đang bị đánh
				{
					//chỉnh hướng theo hướng va chạm với wall
					if (nx < 0) direction = 1;
					else direction = 0;
					isBeingAttacked = 0; //tắt trạng thái be attacked
				}	
				DebugOut(L"%d,%d,%f \n", minClimb, maxClimb, position.y);
			}
			else
			{
		/*		if (isBeingAttacked != 1)
					vy += NINJA_GRAVITY;*/
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
	return iscol;
}

void Ninja::collisionEnemies(vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents; //lưu danh sách cái object có thể va chạm trong frame tới
	vector<LPCOLLISIONEVENT> coEventsResult;//lưu danh sách 2 object gần nhất sẽ va chạm, theo trục x, y

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents); //tính toán coEvents

	if (coEvents.size() == 0)//không có va chạm
	{
		//xét xem có va chạm theo AABB không
		for (UINT i = 0; i < coObjects->size(); i++)
			if (this->checkAABB(coObjects->at(i)) && stillUntouchable()==0)
			{
				
				if (coObjects->at(i)->GetType() == BULLET)
					this->DecreaseHP(2);
				else if (coObjects->at(i)->GetType() == BOSS)
					this->DecreaseHP(3);
				else this->DecreaseHP(1);

				//nếu đang leo tường thì thoát, không chuyển trạng thái
				if (canLatch == 1)
				{
					startUntouchable();
					return;
				}

				if (direction < 1)
				{
					//va chạm từ phải
					SetState(State::BEING_ATTACKED_LEFT);
				}
				else
				{
					//va chạm từ trái
					SetState(State::BEING_ATTACKED_RIGHT);
				}

			}
		return;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		if (nx != 0 || ny != 0) //nếu có va chạm theo swept
		{
			//dựa vào loại quái để trừ HP
			for (int i = 0; i < coEventsResult.size(); i++)
				if (coEventsResult.at(i)->nx != 0)
				{
					if (coEventsResult.at(i)->obj->GetType() == BULLET)
						this->DecreaseHP(2);
					else if (coEventsResult.at(i)->obj->GetType() == BOSS)
						this->DecreaseHP(3);
					else this->DecreaseHP(1);
				}

			//nếu đang leo tường thì thoát, không chuyển trạng thái
			if (canLatch == 1)
			{
				startUntouchable();
				return;
			}
			
			if (direction < 1)
			{
				//va chạm từ phải
				SetState(State::BEING_ATTACKED_LEFT);
			}
			else
			{
				//va chạm từ trái
				SetState(State::BEING_ATTACKED_RIGHT);
			}

			
			
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Ninja::collisionItems()
{
	vector<Item*> coItems;
	coItems = Items::GetInstance()->GetAllItems(); //lấy danh sách item đang xuất hiện trong camera
	for (int i = 0; i < coItems.size(); i++)
	{
		if (checkAABB(coItems[i]))
		{
			coItems[i]->setDie();
			if(AllowSound)
			Sound::GetInstance()->Play(chemitem);
			switch (coItems[i]->getItemType())
			{
			case I_BONUSPOINTBLUE:
				this->score += 500;
				break;
			case I_BONUSPOINTRED:
				this->score += 1000;
				break;
			case I_HEALTH:
				this->DecreaseHP(-6);
				break;
			case I_THROWINGSTAR:
				nowWeapon = weapons[1];
				break;
			case I_WINDMILLSTAR:
				nowWeapon = weapons[2];
				break;
			case I_TIMEFREEZE:
				IsTimeFreeze = true;
				Time::GetInstance()->Pause();
				start_stop = GetTickCount();
				break;
			case I_SPIRITPOINTSBLUE:
				this->strength += 5;
				break;
			case I_SPIRITPOINTSRED:
				this->strength += 10;
				break;
			}
		}
	}
}

void Ninja::processCollision(vector<LPGAMEOBJECT> *Coobjects)
{
	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> walls;
	vector<LPGAMEOBJECT> enemies; //chứa các quái va chạm với ninja
	vector<LPGAMEOBJECT> objects; //chứa các đối tượng va chạm với vũ khí
	bricks.clear();
	walls.clear();
	enemies.clear();
	objects.clear();

	//lọc từ Coobject ra các loại đối tượng cho va chạm
	for (int i = 0; i < Coobjects->size(); i++)
	{
		switch (Coobjects->at(i)->GetType())
		{
		case BRICK:
			bricks.push_back(Coobjects->at(i));
			break;
		case WALL:
			walls.push_back(Coobjects->at(i));
			break;
		case SOLDIERYELLOW:
		case BIRD:
		case DOG:
		case RUNNINGMAN:
		case BAT:
		case BOSS:
			enemies.push_back(Coobjects->at(i));
			objects.push_back(Coobjects->at(i));
			break;
		case MUMMIES:
		{
			Mummies *mum = dynamic_cast<Mummies *>(Coobjects->at(i));
			enemies.push_back(Coobjects->at(i));
			objects.push_back(Coobjects->at(i));
			enemies.push_back(mum->GetWeapon());
			objects.push_back(mum->GetWeapon());
			break;
		}
		case GREENSNIPER:
		{
			GreenSniper *sniper = dynamic_cast<GreenSniper *>(Coobjects->at(i));
			enemies.push_back(Coobjects->at(i));
			objects.push_back(Coobjects->at(i));
			enemies.push_back(sniper->GetBullet());
			objects.push_back(sniper->GetBullet());
			break;
		}
		case SOLDIERGREEN:
		{
			SoldierGreen *soldier = dynamic_cast<SoldierGreen *>(Coobjects->at(i));
			enemies.push_back(Coobjects->at(i));
			objects.push_back(Coobjects->at(i));
			enemies.push_back(soldier->GetBullet());
			objects.push_back(soldier->GetBullet());
			break;
		}
		case BULLET:
			objects.push_back(Coobjects->at(i));
			enemies.push_back(Coobjects->at(i));
			break;
		default:
			objects.push_back(Coobjects->at(i));
			break;
		}
	}


	int isCollideWall = 0;
	if (!collisionWall(&walls)) //nếu đang không bám tường, thì mới xét tới gạch
		collisionBrick(&bricks, isCollideWall);

	//nếu không trong trạng thái untouchable thì mới xét va chạm với quái
	if (!stillUntouchable()) collisionEnemies(&enemies);

	//đang sử dụng kiếm
	if (isHitting)
	{
		int ani = getAnimation();
		int frame = this->animations[ani]->GetCurrentFrame() + 1;
		if (frame > 2) frame = 0;
		ninjaSword->SetPositionSword(position.x, position.y, ani, direction, frame);
		ninjaSword->collisionEnemies(&objects);
	}

	//đang sử dụng phi tiêu, bật active cho phi tiêu đó
	if (isUsingItem)
	{
		if (nowWeapon != NULL)
		{
			if (createStar == 0) //chưa có star nào 
			{
				int str;
				if (nowWeapon->GetType() == THROWINGSTAR) str=strength - 5;
				else str = strength - 10;
				if (str >= 0)
				{
					createStar = 1; //đánh dấu đã tạo
					nowWeapon->SetActive(1); //bật active
					SetStrength(str); //trừ strength
				}
			}
			else nowWeapon->SetActive(1); //đã có star, bật bình thường
		}
			
	}

	//xét va chạm phi tiêu với quái
	if (nowWeapon != NULL && nowWeapon->GetActive() == 1)
	{
		if (nowWeapon->GetType() == THROWINGSTAR)
		{
			ThrowingStar *throwStar = dynamic_cast<ThrowingStar *>(nowWeapon);
			throwStar->collisionEnemies(&objects);
		}
		else
			if (nowWeapon->GetType() == WINDMILLSTAR)
			{
				WindmillStar *windStar = dynamic_cast<WindmillStar *>(nowWeapon);
				windStar->collisionEnemies(&objects);
			}
	}

	//va chạm với items cho ninja
	collisionItems();

}

void Ninja::Update(DWORD dt, vector<LPGAMEOBJECT> *Coobjects)
{
	//DebugOut(L"%d \n", canLatch);
	if (IsKeyPress(DIK_K)) godMode = 1 - godMode;
	if (godMode == 1) HP = 16;
	//check điều kiện ninja chết
	if ((position.y < 0) || (this->HP <= 0) || (Time::GetInstance()->GetTime() <= 0 && isBossDie==false))
	{
		IsNinjaDie = true;
		this->die = true;
		SetNullNowweapon();
	}
	
	//nếu không phải đang bị tấn công, thì update trạng thái
	if (!isBeingAttacked) KeyUpdate(dt);
	
	//set biên trong map của ninja
	int leftEdge = 0;
	int rightEdge = 10000000;
	//lấy biên phải dựa trên num background đang vẽ
	switch (Background::getNumBackGround())
	{
	case 1:
		rightEdge = MAP_WIDTH_1;
		break;
	case 2:
		rightEdge = MAP_WIDTH_2 - 27;
		break;
	case 3:
		leftEdge = 23;
		rightEdge = MAP_WIDTH_3 - 31;
		break;
	}
	
	GameObject::Update(dt); //update dx,dy

	// trọng lực kéo, nếu không phải đang leo tường
	if (!isLatching)
	{
		vy -= GRAVITY;
	}

	// đi tới biên
	if (this->direction > 0 && position.x > rightEdge) position.x = rightEdge;
	if (this->direction < 0 && position.x < leftEdge) position.x = leftEdge;

	//***********************************************************************
	processCollision(Coobjects);
	
	
}

void Ninja::KeyUpdate(DWORD dt)
{
	//bật/tắt godmode
	
//#pragma region Bị tấn công từ phải
//	if (!stillUntouchable() && IsKeyDown(DIK_R))
//	{
//		this->SetState(State::BEING_ATTACKED_RIGHT);
//		return;
//	}
//#pragma endregion
//
//#pragma region Bị tấn công từ trái
//	if (!stillUntouchable() && IsKeyDown(DIK_T))
//	{
//		this->SetState(State::BEING_ATTACKED_LEFT);
//		return;
//	}
//#pragma endregion

#pragma region leo tường
	if (canClimb>0 && this->GetisLatching() && (IsKeyDown(DIK_UP)))
	{
		this->SetState(State::CLIMB_UP);
		return;
	}
	if (canClimb>0 && this->GetisLatching() && IsKeyDown(DIK_DOWN))
	{
		this->SetState(State::CLIMB_DOWN);
		return;
	}
#pragma endregion

#pragma region nhảy khỏi tường
	if (IsKeyDown(DIK_SPACE) && IsKeyDown(DIK_RIGHT) && this->GetisLatching() && this->GetDirection() <= 0) {
		this->SetState(State::JUMPWALL_RIGHT);
		return;
	}
	if (IsKeyDown(DIK_SPACE) && IsKeyDown(DIK_LEFT) && this->GetisLatching() && this->GetDirection()>0)
	{
		this->SetState(State::JUMPWALL_LEFT);
		return;
	}
#pragma endregion
	
#pragma region va chạm tường
		if (canLatch>0)
		{
			this->SetState(State::LATCH);
			return;
		}
#pragma endregion


	if (this->isLatching) return;


	if (IsKeyDown(DIK_SPACE))
	{
		if (!this->isJumping)
			this->SetState(State::JUMP);
		return;
	}
#pragma region vừa chạy vừa đánh
	if (IsKeyDown(DIK_S) && IsKeyDown(DIK_RIGHT))
	{
		this->SetState(State::WALKING_RIGHT);
		this->SetState(State::STAND_HIT);
		return;
	}
	if (IsKeyDown(DIK_S) && IsKeyDown(DIK_LEFT))
	{
		this->SetState(State::WALKING_LEFT);
		this->SetState(State::STAND_HIT);
		return;
	}
#pragma endregion

#pragma region vừa ngồi vừa đánh
	if (IsKeyDown(DIK_S) && IsKeyDown(DIK_DOWN))
	{
		this->SetState(State::SIT_HIT);
		return;
	}
#pragma endregion

#pragma region vừa ngồi vừa chạy
	if (IsKeyDown(DIK_DOWN) && IsKeyDown(DIK_RIGHT))
	{
		this->SetState(State::WALKING_RIGHT);
		return;
	}
	if (IsKeyDown(DIK_DOWN) && IsKeyDown(DIK_LEFT))
	{
		this->SetState(State::WALKING_LEFT);
		return;
	}
#pragma endregion

#pragma region vừa ngồi vừa đánh
	if (IsKeyDown(DIK_S) && IsKeyDown(DIK_DOWN))
	{
		this->SetState(State::WALKING_RIGHT);
		this->SetState(State::STAND_HIT);
		return;
	}
	if (IsKeyDown(DIK_S) && IsKeyDown(DIK_LEFT))
	{
		this->SetState(State::WALKING_LEFT);
		this->SetState(State::STAND_HIT);
		return;
	}
#pragma endregion
	//if ((ninja->GetisHitting() > 0)) return;
	//if ((ninja->isHitting)>0) return;
	if (IsKeyDown(DIK_RIGHT))
		this->SetState(State::WALKING_RIGHT);
	else if (IsKeyDown(DIK_LEFT))
		this->SetState(State::WALKING_LEFT);
	else if (IsKeyDown(DIK_DOWN))
		this->SetState(State::SIT);
	else if (IsKeyDown(DIK_S))
		this->SetState(State::STAND_HIT);
	else if (IsKeyDown(DIK_F))
		this->SetState(State::USE_ITEM);
	else this->SetState(State::IDLE);
}

int Ninja::getAnimation()
{
	int ani;
#pragma region chọn animation tương ứng với trạng thái
	if (die == true) ani = NINJA_ANI_DIE;
	else
		if (isBeingAttacked > 0)
			ani = NINJA_ANI_BEING_ATTACKED;
		else
			if (isLatching)
			{
				if (isClimbing)
					ani = NINJA_ANI_CLIMB;
				else
					ani = NINJA_ANI_LATCH;
			}
			else
				if (isJumping)
				{
					if (isHitting > 0)
						ani = NINJA_ANI_STAND_HIT;
					else
						ani = NINJA_ANI_JUMP;
				}
				else
					if (isHitting > 0)
					{
						if ((this->isSitting) == 0)
							ani = NINJA_ANI_STAND_HIT;
						else
							ani = NINJA_ANI_SIT_HIT;
					}
					else
						if (isUsingItem > 0)
						{
							ani = NINJA_ANI_USE_ITEM;
						}
						else
						{
							if (vx == 0)
							{
								if (this->isSitting == 0) //nhân vật không ngồi
									ani = NINJA_ANI_IDLE;
								else
									ani = NINJA_ANI_SIT;
							}
							else
								ani = NINJA_ANI_WALKING;
						}

#pragma endregion
	return ani;
}

void Ninja::Render()
{
	int ani;
	ani = getAnimation();

	if (unTouchable && !isBeingAttacked) //mới bị tấn công xong, chuyển qua trạng thái nhấp nháy
	{
		flicker = !flicker;//biến cờ để render nhấp nháy
	}
	else flicker = 0;

	int lientuc=0;
	//2 trạng thái ninja đánh liên tục là: chém và sử dụng item
	if (isHitting == 1) lientuc = isHitting;
	else lientuc = isUsingItem;

	if(godMode==0)
	animations[ani]->Render(position.x, position.y, lientuc, this->GetDirection(),xx,yy, w, h,-1,flicker==true?NHAY_MOTMAU:KHONG_NHAY,-1,false);
	else
		animations[ani]->Render(position.x, position.y, lientuc, this->GetDirection(), xx, yy, w, h, -1, GODMODE, -1, false);
	//cập nhật biến cờ đánh hoặc dùng item
	if (isHitting > 0) isHitting = lientuc;
	else isUsingItem = lientuc;

	//RenderBoundingBox();

	//render kiếm nếu đang chém
	if (isHitting == 1)
	{
		ninjaSword->Render(position.x,position.y,ani,direction,this->animations[ani]->GetCurrentFrame());
	}
	
	//render phi tiêu nếu đang dùng phi tiêu
	if (nowWeapon != NULL && nowWeapon->GetActive() == 1)
	{

		if (nowWeapon->GetType() == THROWINGSTAR)
		{
			ThrowingStar *star = dynamic_cast<ThrowingStar *>(nowWeapon);
			star->Render(position.x, position.y, ani, direction, this->animations[ani]->GetCurrentFrame(), this->dt);
		}
		else
		{
			WindmillStar *xstar = dynamic_cast<WindmillStar *>(nowWeapon);
			xstar->Render(position.x, position.y, ani, direction, this->animations[ani]->GetCurrentFrame(), this->dt);
		}


	}
	
}

void Ninja::SetState(State state)
{
	if (isHitting > 0 && state!=State::BEING_ATTACKED_LEFT && state != State::BEING_ATTACKED_RIGHT) return;
	if (isUsingItem > 0) return;
	isSitting = 0;
	this->state = state;
	switch (state)
	{
#pragma region use item
	case USE_ITEM:
		isUsingItem = 1;
		if (!this->isJumping) vx = 0;
		break;
#pragma endregion
#pragma region being attacked
	case BEING_ATTACKED_RIGHT:
		if (godMode == 0)
		{
			isHitting = 0;
			startUntouchable();
			vy = JUMP_SPEED_Y / 2;
			vx = -WALKING_SPEED / 2;
			direction = 1;
			isBeingAttacked = 1;
			if (AllowSound)
			Sound::GetInstance()->Play(untouch);
		}
		break;
	case BEING_ATTACKED_LEFT:
		if (godMode == 0)
		{
			isHitting = 0;
			startUntouchable();
			vy = JUMP_SPEED_Y / 2;
			vx = WALKING_SPEED / 2;
			direction = 0;
			isBeingAttacked = 1;
			if (AllowSound)
			Sound::GetInstance()->Play(untouch);
		}
		break;
#pragma endregion
#pragma region latch
	case LATCH:
		isLatching = 1;
		isClimbing = 0;
		isBeingAttacked = 0;
		vy = 0;
		vx = 0;
		break;
#pragma endregion
#pragma region walking
	case WALKING_RIGHT:
		vx = WALKING_SPEED;
		direction = 1;
		break;
	case WALKING_LEFT:
		vx = -WALKING_SPEED;
		direction = -1;
		break;
#pragma endregion
#pragma region jump
	case JUMP:
		if (isJumping<1)
			vy = JUMP_SPEED_Y;
		isJumping = 1;
		if (AllowSound)
		Sound::GetInstance()->Play(ninjajump);
		break;
#pragma endregion
#pragma region hit
	case STAND_HIT:
		isHitting = 1;
		if (!this->isJumping) vx = 0;
		if (AllowSound)
		Sound::GetInstance()->Play(chem);
		break;
	case SIT_HIT:
		isSitting = 1;
		vx = 0;
		isHitting = 1;
		if (AllowSound)
		Sound::GetInstance()->Play(chem);
		break;
#pragma endregion
#pragma region climb
	case CLIMB_UP:
		vy = 0;
		if (position.y < maxClimb)
			vy = NINJA_CLIMB_SPEED;
		isLatching = 1;
		isClimbing = 1;
		break;
	case CLIMB_DOWN:
		vy = 0;
		if (position.y - 32 > minClimb)
			vy = -NINJA_CLIMB_SPEED;
		isLatching = 1;
		isClimbing = 1;
		break;
#pragma endregion
#pragma region jump wall
	case JUMPWALL_RIGHT:
		direction = 1;
		isLatching = 0;
		isClimbing = 0;
		isJumpWall = 0;
		isJumping = 1;
		canLatch = 0;
		vx = WALKING_SPEED;
		vy = JUMP_SPEED_Y / 2;
		break;
	case JUMPWALL_LEFT:
		direction = -1;
		isLatching = 0;
		isClimbing = 0;
		isJumpWall = 0;
		canLatch = 0;
		isJumping = 1;
		vx = -WALKING_SPEED;
		vy = JUMP_SPEED_Y / 2;
		break;
#pragma endregion
#pragma region sit
	case SIT:
		isSitting = 1;
		vx = 0;
		break;
#pragma endregion
#pragma region die
	case DIE:
		vx = 0;
		vy = 0;
		break;
#pragma endregion
#pragma region idle
	default:
		this->state = IDLE;
		vx = 0;
		break;
#pragma endregion
	}
}


void Ninja::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	D3DXVECTOR3 p = position;
	p = Camera::GetInstance()->Transform(p);
	l = p.x;
	t = p.y;

	int ww=0, hh=0;
	switch (this->state)
	{
	case BEING_ATTACKED_LEFT: case BEING_ATTACKED_RIGHT:
		ww = NINJA_BE_ATTACK_W;
		hh = NINJA_BE_ATTACK_H;
		break;
	case JUMPWALL_LEFT:case JUMPWALL_RIGHT:
		ww = NINJA_JUMP_W;
		hh = NINJA_JUMP_H;
		break;
	case LATCH:
		ww = NINJA_LATCH_W;
		hh = NINJA_LATCH_H;
		break;
	case CLIMB_UP: case CLIMB_DOWN:
		ww = NINJA_CLIMB_W;
		hh = NINJA_CLIMB_H;
		break;
	case IDLE:
		ww = NINJA_IDLE_W;
		hh = NINJA_IDLE_H;
		break;
	case STAND_HIT: 
		
		ww = NINJA_ATTACK_W;
		hh = NINJA_ATTACK_H;
		break;
	case WALKING_RIGHT: case WALKING_LEFT:
		
		ww = NINJA_WALK_W;
		hh = NINJA_WALK_H;
		break;
	case SIT_HIT:
		ww = NINJA_SITATTACK_W;
		hh = NINJA_SITATTACK_H;
		break;
	case JUMP:
		ww = NINJA_JUMP_W;
		hh = NINJA_JUMP_H;
		break;
	case SIT:
		ww = NINJA_SIT_W;
		hh = NINJA_SIT_H;
		break;
	default:
		ww = NINJA_IDLE_W;
		hh = NINJA_IDLE_H;
		break;
	}
	r = l + ww;
	b = t + hh;
}
