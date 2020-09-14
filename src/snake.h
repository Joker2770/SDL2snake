/*************************************************************************
    > File Name: snake.h
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Tue Sep  8 09:03:57 2020
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

#ifndef __SNAKE_H__
#define __SNAKE_H__

#ifdef _WIN32
//Windows
extern "C"
{
#include "SDL.h"
};
#else
//Linux
//Linux C++
#ifdef __cplusplus
extern "C"
{
#endif
	
#include<SDL2/SDL.h>

//Linux C++
#ifdef __cplusplus
};
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

typedef struct snake_node
{
	int x_pos;
	int y_pos;
	struct snake_node* next;
}SnakeNode, *SnakeList;

class Snake
{
	public:
		Snake() : m_iLength(1)
		{
			switch(rand()%4)
			{
				case 0:
					this->m_CurDirection = UP;
					break;
				case 1:
					this->m_CurDirection = DOWN;
					break;
				case 2:
					this->m_CurDirection = LEFT;
					break;
				case 3:
					this->m_CurDirection = RIGHT;
					break;
				default:
					this->m_CurDirection = LEFT;
					break;
			}
		}
		~Snake()
		{
		}

	public:
		void initSelf();
		void moveSelf(DRIVER_DIRECTION Direction);
		void eatfood();
		SDL_Rect* drawSelf(SnakeList m_snake);
		void growSelf();
		bool isEatSelf();
		bool isAlive();

	private:
		SnakeList m_snake;
		int m_iLength;
		DRIVER_DIRECTION m_CurDirection;

};

#endif
