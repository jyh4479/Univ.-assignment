#pragma once
class SnakeCtrl
{
public:
	SnakeCtrl();
	~SnakeCtrl();

	int posx;
	int posy;
	int direction;
	SnakeCtrl* next;
};

class Food
{
public:
	int posx;
	int posy;
};

void CreateSnake(SnakeCtrl ** mHead);
void DeleteSnake(SnakeCtrl ** mHead);
void CreateFood(Food** mFood);
void MoveSnake(UINT SetMove, SnakeCtrl * mHead);

BOOL HitWall(SnakeCtrl * mHead);
BOOL HitBody(const SnakeCtrl * mHead);
BOOL EatFood(SnakeCtrl ** mHead, Food * Body);

