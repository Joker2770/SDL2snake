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

void Snake::eatfood()
{

}

void Snake::initSelf()
{
	this->m_snake->x_pos = SCREEN_WIDTH / 2;
	this->m_snake->y_pos = SCREEN_HEIGHT / 2;
	this->m_snake->next = (SnakeList)malloc(sizeof(SnakeNode));
	this->m_snake->next->x_pos = this->m_snake->x_pos + 10;
	this->m_snake->next->y_pos = this->m_snake->y_pos;
	this->m_snake->next->next = NULL;
	//this->m_iLength = 2;
}

bool Snake::isAlive()
{
	if (this->m_snake->x_pos > SCREEN_WIDTH || this->m_snake->x_pos < 0 || this->m_snake->y_pos > SCREEN_HEIGHT || this->m_snake->y_pos < 0)
		return false;

	if (this->isEatSelf())
		return false;

	return true;
}

void Snake::moveSelf(DRIVER_DIRECTION iDir)
{

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
