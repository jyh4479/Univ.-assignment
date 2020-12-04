#include "stdafx.h"
#include "SnakeCtrl.h"


SnakeCtrl::SnakeCtrl()
{
}


SnakeCtrl::~SnakeCtrl()
{
}

void CreateSnake(SnakeCtrl **mHead) //The information of Snake
{
	SnakeCtrl *tmp; //Declare tmp
	SnakeCtrl *newNode; //Declare newNode
	int i = 0; 

	tmp = (*mHead); //Save mHead to tmp

	for (i = 0; i <= 2; i++) //Repeat the function
	{
		if (tmp == NULL) //This function Saves information to mHead
		{
			newNode = new SnakeCtrl;
			newNode->direction = VK_LEFT; //Starting direction is left
			newNode->posx = 30 / 2 + i; //The information of position
			newNode->posy = 20 / 2;
			(*mHead) = newNode; //Save newNode to mHead
			tmp = (*mHead); //Save mHead to tmp
		}

		else if (tmp != NULL) //This function Saves information to body
		{
			newNode = new SnakeCtrl;
			newNode->direction = VK_LEFT;
			newNode->posx = 30 / 2 + i;
			newNode->posy = 20 / 2;
			tmp->next = newNode;
			tmp = tmp->next;
			tmp->next = NULL;
		}
	}
}

void DeleteSnake(SnakeCtrl **mHead) //The function of delete snake
{
	SnakeCtrl *tmp; //Declare tmp

	tmp = (*mHead); //Save mHead to tmp

	while (tmp) //Delete all snake
	{
		(*mHead) = tmp->next; //Save tmp->next to mHead (changing head)
		delete tmp; //delete tmp
		tmp = (*mHead); //Save mHead to tmp
	}
}

void CreateFood(Food ** mFood) //The function that creates first Food
{	
	Food *Foodpos; //Declare variable for saveing information of Food
	srand(time(0));
	(*mFood) = new Food; //Create Food's Node
	Foodpos = (*mFood);

	Foodpos->posx = (rand()%30)+1; //Save random value that using position
	Foodpos->posy = (rand()%20)+1;
}

void MoveSnake(UINT nChar,SnakeCtrl *mHead) //The function works for moving snake
{
	SnakeCtrl *bodyPos = mHead; //Declare bodyPos and Save mHead to bodyPos
	int Front;
	int Back;

	Front = mHead->direction; //Save mHead direction to Front

	if (nChar != NULL) //If user press any key, practice the function
		mHead->direction = nChar; //mHead's direction is nChar

	while (bodyPos->next != NULL) //Repeat the function If bodyPos->next is not NULL
	{
		bodyPos = bodyPos->next; //Save bodyPos->next to bodyPos
		Back = bodyPos->direction; //Save bodyPos->direction to Back
		bodyPos->direction = Front; //Save Front to bodyPos->direction
		Front = Back; //Save Back to Front
	}

	bodyPos = mHead; //Save mHead to bodyPos
	while (bodyPos != NULL) //Repeat the function If bodyPos is not NULL
	{
		switch (bodyPos->direction) //Define position according to body direction information
		{
		case VK_DOWN: //If direction is Down
			bodyPos->posy += 1; //position y = y+1
			break;
		case VK_UP: //If direction is Up
			bodyPos->posy -= 1; //position y = y-1
			break;
		case VK_LEFT: //If direction is Left
			bodyPos->posx -= 1; //position x = x-1
			break;
		case VK_RIGHT: //If direction is Right
			bodyPos->posx += 1; //position x = x+1
			break;
		}
		bodyPos = bodyPos->next; //Save bodyPos->next to bodyPos
	}
}

BOOL HitWall(SnakeCtrl* mHead) //Check hit wall
{
	if (!(mHead->posy > 0 && mHead->posy <= 20) || //A function that checks a wall for a collision
		!(mHead->posx > 0 && mHead->posx <= 30))
		return 1;
	else
		return  0;
}

BOOL HitBody(const SnakeCtrl *mHead) //Check hit body
{
	SnakeCtrl *bodyPos = (SnakeCtrl*)mHead->next; //Store the body after head in bodypos
	while (bodyPos != NULL)
	{
		if (bodyPos->posx == mHead->posx && bodyPos->posy == mHead->posy)
			return 1; //Return 1 if body position and head position are the same
		
		bodyPos = bodyPos->next; //Check by turning to next body
	}
	return 0;
}

BOOL EatFood(SnakeCtrl** mHead, Food *Food) //Check, if the snake eat the Food
{
	SnakeCtrl* NewHead;
	SnakeCtrl* bodyPos = *mHead;
	BOOL  checking = 0;

	if ((*mHead)->posy != Food->posy || (*mHead)->posx != Food->posx)
		return 0; //If the head position and food position are not the same, do it.
	
	NewHead = new SnakeCtrl; //Create New Node
	NewHead->direction = (*mHead)->direction; //Save Head's direction to New Node's direction

	NewHead->posx = Food->posx; //Save information of position to New Node
	NewHead->posy = Food->posy;

	switch (NewHead->direction) //Function for position of newly created head
	{
	case VK_DOWN: //If press down
		NewHead->posy += 1; //position y = y+1
		break;
	case VK_UP: //If press up
		NewHead->posy -= 1; //position y = y-1
		break;
	case VK_LEFT: //If press left
		NewHead->posx -= 1; //position x = x-1
		break;
	case VK_RIGHT: //If press right
		NewHead->posx += 1; //position y = x+1
		break;
	}

	NewHead->next = *mHead; //Connect New Node
	*mHead = NewHead; //Save NewHead to mHead

	while (1) //Create new Food and Check not to let food appear on the snake's body
	{
		Food->posx = (rand() % 30) + 1; //Save the information of position of Food
		Food->posy = (rand() % 20) + 1;

		checking = 0;
		bodyPos = *mHead; //Save mHead to bodyPos
		while (bodyPos != NULL) //If bodyPos is not NULL, repeat the function
		{
			if (bodyPos->posx == Food->posx && bodyPos->posy == Food->posy)
			{//If the position of the food received at random is the same as that of the snake, repeat the function over and over again.
				checking = 1;
				break;
			}
			bodyPos = bodyPos->next; //Check by turning to next body
		}

		if (checking == 0) //If checking is 0
			break; //practice the break
	}
	return 1;
}

