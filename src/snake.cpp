/*************************************************************************
    > File Name: snake.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sun Sep 13 11:58:56 2020
 ************************************************************************/
 
/*
MIT License

Copyright (c) 2020 Joker2770

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "snake.h"
#include<iostream>
using namespace std;

bool Snake::isAlive()
{
	if (this->m_snake->x_pos > SCREEN_WIDTH || this->m_snake->x_pos < 0 || this->m_snake->y_pos > SCREEN_HEIGHT || this->m_snake->y_pos < 0)
		return false;

	if (this->isEatSelf())
		return false;

	return true;
}

void Snake::moveSelf()
{
	//Update length
	this->m_iLength = countSnakeLength(this->m_snake);

	printf("CurDirection = %d\n", this->m_CurDirection);
	printList(this->m_snake);

	int tmp = 0;
	switch (this->m_CurDirection)
	{
	case UP:
		tmp = this->m_snake->y_pos - 10;
		this->m_snake = insertNode(this->m_snake, 0, this->m_snake->x_pos, tmp);
		break;
	case DOWN:
		tmp = this->m_snake->y_pos + 10;
		this->m_snake = insertNode(this->m_snake, 0, this->m_snake->x_pos, tmp);
		break;
	case LEFT:
		tmp = this->m_snake->x_pos - 10;
		this->m_snake = insertNode(this->m_snake, 0, tmp, this->m_snake->y_pos);
		break;
	case RIGHT:
		tmp = this->m_snake->x_pos + 10;
		this->m_snake = insertNode(this->m_snake, 0, tmp, this->m_snake->y_pos);
		break;
	default:
		break;
	}
	//Update length
	this->m_iLength = countSnakeLength(this->m_snake);

	if (!this->isEating)
		this->m_snake = deleteNode(this->m_snake, this->m_iLength);
	else
		printf("Snake eating food...\n");
	//Change isEating flag
	this->isEating = false;

	printList(this->m_snake);

	//Update length
	this->m_iLength = countSnakeLength(this->m_snake);
}

void Snake::changeDirection(DRIVER_DIRECTION direction)
{
	switch (direction)
	{
	case UP:
		if (DOWN != this->m_CurDirection)
			this->m_CurDirection = UP;
		break;
	case DOWN:
		if (UP != this->m_CurDirection)
			this->m_CurDirection = DOWN;
		break;
	case LEFT:
		if (RIGHT != this->m_CurDirection)
			this->m_CurDirection = LEFT;
		break;
	case RIGHT:
		if (LEFT != this->m_CurDirection)
			this->m_CurDirection = RIGHT;
		break;
	default:
		break;
	}
}

bool Snake::isEatSelf()
{
	SnakeList pS = this->m_snake->next;
	while (NULL != pS)
	{
		if (pS->x_pos == this->m_snake->x_pos && pS->y_pos == this->m_snake->y_pos)	return true;
		pS = pS->next;	
	}

	return false;
}

SDL_Rect* Snake::drawSelf()
{
	SnakeList pSnake = this->m_snake;
	for (int i = 0; pSnake != NULL; i++)
	{
		this->m_sRec[i] = { pSnake->x_pos, pSnake->y_pos, 10, 10 };
		pSnake = pSnake->next;
	}
	return this->m_sRec;
}
