#include "GameObject.h"
#include <algorithm>
#include <WinUser.h>

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

void GameObject::DecreaseHP(int damage)
{
	HP -= damage;
	if (HP < 0) HP = 0;
	if (HP > 16) HP = 16;
}

void GameObject::SetActive(int x)
{
	IsActive = x;
	if (x == 0)
	{
		direction = initdirection;
		position = initposition;
		vx = InitVx;
	}
}

GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;
	vx = vy = 0;
	direction = 1;
	IsActive = 0;
	IsContainer = false;
	die = false;
}

void GameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}


void GameObject::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	D3DXVECTOR3 p1 = position;
	if (type == BOSS)
	{
		p1.x += 110;
		p1.y += 70;
	}
	if (type != BRICK && type != WALL)
	{
		p1.x -= 2;
		p1.y += 2;
		w = w + 2;
		h = h + 2;
	}
	p1 = Camera::GetInstance()->Transform(p1);
	l = p1.x;
	t = p1.y;

	r = l + w;
	b = t + h;
}

void GameObject::RenderBoundingBox()
{
	float l, t, r, b;

	GameObject::GetBoundingBox(l, t, r, b);
	D3DXVECTOR3 p = D3DXVECTOR3(l, t, 0);


	if (direction <= 0)
	{
		p.x += xx;
	}
	p.y -= yy;

	RECT rect;
	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(6);

	rect.left = 0;
	rect.top = 0;
	rect.right = ((int)r - (int)l);
	rect.bottom = ((int)b - (int)t);
	LPD3DXSPRITE spriteHandler = Graphic::GetInstance()->GetSpriteHandler();
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	spriteHandler->Draw(bbox, &rect, NULL, &p, D3DCOLOR_ARGB(90, 255, 255, 255));
	spriteHandler->End();
}

bool GameObject::IsInCamera()
{
	int xCam = Camera::GetInstance()->GetPosition().x;
	int yCam = Camera::GetInstance()->GetPosition().y;
	if (position.x+w<xCam || position.x>xCam + GAME_WIDTH)
		return false;
	if (position.y <= 0 || position.y >= GAME_HEIGHT)
		return false;
	return true;
}

GameObject::~GameObject()
{
	animations.clear();
}

void GameObject::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float &t, float &nx, float &ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;
	t = -1.0f;			// no collision
	nx = ny = 0;
	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx -sdx;
	float dy = -this->dy +sdy;

	GetBoundingBox(ml, mt, mr, mb);

	RECT dest;
	RECT box1;
	box1.left = ml;
	box1.top = mt;
	box1.right = mr;
	box1.bottom = mb;
	RECT box2;
	box2.left = sl;
	box2.top = st;
	box2.right = sr;
	box2.bottom = sb;

	if (!IntersectRect(&dest, &box1, &box2))
	{
		SweptAABB(
			ml, mt, mr, mb,
			dx, dy,
			sl, st, sr, sb,
			t, nx, ny
		);
	}

	CollisionEvent * e = new CollisionEvent(t, nx, ny, coO);
	return e;
}

void GameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void GameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}


	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


bool GameObject::checkAABB(LPGAMEOBJECT obj)
{
	RECT dest;
	RECT box1;
	float ml, mt, mr, mb;
	obj->GetBoundingBox(ml, mt, mr, mb);
	box1.left = ml;
	box1.top = mt;
	box1.right = mr;
	box1.bottom = mb;
	float sl, st, sr, sb;
	this->GetBoundingBox(sl, st, sr, sb);
	RECT box2;
	box2.left = sl;
	box2.top = st;
	box2.right = sr;
	box2.bottom = sb;
	if (IntersectRect(&dest, &box1, &box2))
	{
		return true;
	}
	return false;
}