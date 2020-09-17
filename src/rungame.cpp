/*************************************************************************
    > File Name: rungame.cpp
    > Author: Jintao Yang
    > Mail: 18608842770@163.com 
    > Created Time: Mon Sep  7 08:40:32 2020
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

#ifdef _WIN32
//Windows
extern "C"
{
#include <windows.h> //Use Sleep().
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
#include<unistd.h>

//Linux C++
#ifdef __cplusplus
};
#endif
#endif

#include <stdio.h>
#include"config.h"
#include"snake.h"
#include"food.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void closeAll();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

int main(int argc, char *argv[])
{
	Snake *snake = new Snake();
	Food *food = new Food();
	SDL_Rect *pSRec = (SDL_Rect *)malloc((SCREEN_WIDTH*SCREEN_HEIGHT / 100) * sizeof(SDL_Rect));
	
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				//Clear screen
				printf("Clear screen!\n");
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				
				//Render red filled quad
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				food->beEaten = true;
				SDL_RenderFillRect(gRenderer, food->drawSelf());

				snake->initSelf();
				memset(pSRec, 0, sizeof(pSRec));
				pSRec = snake->drawSelf();
				for (int i = 0; i < snake->m_iLength; i++)
				{
					//Render green filled quad
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderFillRect(gRenderer, &pSRec[i]); 
					//Render blue outlined quad
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
					SDL_RenderDrawRect(gRenderer, &pSRec[i]);
				}

				//Update screen
				SDL_RenderPresent(gRenderer);

#ifdef _WIN32
				Sleep(2000);
#else
				sleep(2);
#endif

			}
		}
	}
	closeAll();
	
	if (NULL != food)
	{
		delete food;
		food = NULL;
	}	
	
	if (NULL != snake)
	{
		delete snake;
		snake = NULL;
	}

	if (NULL != pSRec)
	{
		free(pSRec);
		pSRec = NULL;
	}

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}

		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void closeAll()
{
	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
