/*************************************************************************
    > File Name: SnakeLinkList.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sat Sep 19 14:44:39 2020
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

#include "SnakeLinkList.h"
#include <stdlib.h>

int countSnakeLength(SnakeList snake)
{
	if (NULL == snake)
		return 0;

	SnakeList pFound = snake;
	int i = 0;
	while (NULL != snake)
	{
		pFound = pFound->next;
		i++;
	}

	return i;
}

SnakeList foundNode(SnakeList pHead, int idx)
{
	if (NULL == pHead || idx < 0)
		return NULL;

	SnakeList pFound = pHead;
	for(int i = 1; NULL != pFound; i++)
	{
		if (idx == i)
		{
			return pFound;
		}
		pFound = pFound->next;
	}
	return NULL;
}

SnakeList insertNode(SnakeList pHead, int idx, int x, int y)
{
	SnakeList p = (SnakeList)malloc(sizeof(SnakeNode));
	if (NULL == p) return pHead;
	SnakeList q, pe;
	q = pe = pHead;

	p->x_pos = x;
	p->y_pos = y;

	//pHead is NULL
	if (NULL == pHead)
	{
		p->next = NULL;
		pHead = p;
		return pHead;
	}

	int iCount = countSnakeLength(pHead);
	//to the first
	if (1 > idx)
	{
		p->next = q;
		pHead = p;
		return pHead;
	}
	//to the end
	else if (iCount <= idx)
	{
		while (pe->next != NULL)
		{
			pe = pe->next;
		}
		if (NULL != pe)
		{
			p->next = NULL;
			pe->next = p;
		}
		return pHead;
	}
	else
	{
		q = foundNode(pHead, idx);
		p->next = q->next;
		q->next = p;
		return pHead;
	}
}

SnakeList deleteNode(SnakeList pHead, int idx)
{
	SnakeList p = pHead;
	SnakeList q = NULL;

	if (NULL == p)
		return pHead;

	int icount = countSnakeLength(pHead);
	if (idx < 1 || idx > icount)
		return pHead;

	if (1 == idx)
	{
		pHead = pHead->next;
		free(p);
		p = NULL;
	}
	else
	{
		p = foundNode(pHead, idx-1);
		q = p->next;
		if (idx == icount)
			p->next = NULL;
		else
			p->next = q->next;
		free(q);
		q = NULL;
	}

	return pHead;
}

void cleanSnakeNode(SnakeList pHead)
{
	SnakeList p = pHead;
	SnakeList q = p;
	while (NULL != p)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

