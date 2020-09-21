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
#include "SnakeLinkList.h"

class Snake
{
	public:
		Snake() : m_iLength(2), isEating(false), m_drag(2000000)
		{
			this->m_snake = NULL;
			this->m_snake = insertNode(this->m_snake, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			this->m_snake = insertNode(this->m_snake, 0, SCREEN_WIDTH / 2 + 10, SCREEN_HEIGHT / 2);
			printList(this->m_snake);

			this->m_sRec[SCREEN_WIDTH*SCREEN_HEIGHT / 100] = {};

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
			cleanSnakeNode(this->m_snake);
		}

	public:
		void moveSelf();
		void changeDirection(DRIVER_DIRECTION direction);
		SDL_Rect* drawSelf();
		bool isEatSelf();
		bool isAlive();

	public:
		SnakeList m_snake;
		int m_iLength;
		int m_drag;
		bool isEating;
		//At most (SCREEN_WIDTH*SCREEN_HEIGHT / 100) snake nodes;
		SDL_Rect m_sRec[SCREEN_WIDTH*SCREEN_HEIGHT / 100];

	private:
		DRIVER_DIRECTION m_CurDirection;

};

#endif
