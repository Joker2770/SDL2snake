/*************************************************************************
    > File Name: SnakeLinkList.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Sat Sep 19 14:44:39 2020
 ************************************************************************/

/*
 MIT License

 Copyright (c) 2020-2023 Joker2770

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
	while (NULL != pFound)
	{
		pFound = pFound->next;
		i++;
	}

	return i;
}

void printList(SnakeList pHead)
{
	int iCount = countSnakeLength(pHead);
	SnakeList pF = NULL;
	printf("PosList: ");
	for (int i = 0; i < iCount; i++)
	{
		pF = foundNode(pHead, i);
		printf("(%d, %d) ", pF->x_pos, pF->y_pos);
	}
	printf("\n");
}

SnakeList foundNode(SnakeList pHead, unsigned int idx)
{
	if (NULL == pHead)
		return NULL;

	SnakeList pFound = pHead;
	for (int i = 0; NULL != pFound; i++)
	{
		if (idx == i)
		{
			return pFound;
		}
		pFound = pFound->next;
	}
	return NULL;
}

SnakeList insertNode(SnakeList pHead, unsigned int idx, int x, int y)
{
	SnakeList p = (SnakeList)malloc(sizeof(SnakeNode));
	if (NULL == p)
		return pHead;

	p->x_pos = x;
	p->y_pos = y;
	p->next = NULL;

	//pHead is NULL
	if (NULL == pHead)
	{
		printf("NULL == pHead\n");
		pHead = p;
		return pHead;
	}

	int iCount = countSnakeLength(pHead);
	//to the first
	if (0 == idx)
	{
		printf("to the first\n");
		p->next = pHead;
		pHead = p;
	}
	//to the end
	else if (idx >= iCount)
	{
		printf("to the end\n");
		SnakeList pe = NULL;
		pe = foundNode(pHead, iCount - 1);
		if (NULL != pe)
		{
			pe->next = p;
		}
	}
	else
	{
		SnakeList q = NULL;
		q = foundNode(pHead, idx);
		if (NULL != q)
		{
			p->next = q->next;
			q->next = p;
		}
	}
	return pHead;
}

SnakeList deleteNode(SnakeList pHead, unsigned int idx)
{
	SnakeList p = pHead;
	SnakeList tmp = NULL;

	if (NULL == p)
		return pHead;

	int icount = countSnakeLength(pHead);
	if (idx >= icount)
		return pHead;

	printf("idx = %u\n", idx);
	if (0 == idx)
	{
		pHead = pHead->next;
		free(p);
		p = NULL;
	}
	else if (idx == icount - 1)
	{
		p = foundNode(pHead, idx - 1);
		tmp = p->next;
		free(tmp);
		tmp = NULL;
		p->next = NULL;
	}
	else
	{
		p = foundNode(pHead, idx - 1);
		tmp = p->next;
		p->next = p->next->next;
		free(tmp);
		tmp = NULL;
	}

	return pHead;
}

void cleanSnakeNode(SnakeList pHead)
{
	printf("clean...\n");
	SnakeList p = pHead;
	SnakeList q = NULL;
	while (NULL != p)
	{
		q = p;
		p = p->next;
		q->next = NULL;
		free(q);
		q = NULL;
	}
}
