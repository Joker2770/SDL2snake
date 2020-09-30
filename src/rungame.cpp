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
#include <windows.h> //Use Sleep().
extern "C"
{
#include "SDL.h"
#include "SDL_ttf.h"
};
#else
//Linux
//Linux C++
#include<unistd.h>	//Use Sleep().
#ifdef __cplusplus
extern "C"
{
#endif
	
#include<SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//Linux C++
#ifdef __cplusplus
};
#endif
#endif

#include <stdio.h>
#include <time.h>
#include "config.h"
#include "snake.h"
#include "food.h"
#include "renderer.h"

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

//Globally used font
TTF_Font *gFont = NULL;

int main(int argc, char *argv[])
{
	//Initialize the random number seed for rand()
	srand((unsigned)time(NULL));

	Snake *snake = new Snake();
	Food *food = new Food();
	Renderer *LRenderer = new Renderer();
	
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
			//Render text
			SDL_Color textColor = { 0, 0, 0, 0 };
			if (LRenderer->loadFromRenderedText(gRenderer, gFont, "Ready...", textColor))
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				LRenderer->render(gRenderer, (SCREEN_WIDTH - LRenderer->getWidth()) / 2, (SCREEN_HEIGHT - LRenderer->getHeight()) / 2);
				printf("LRenderer: w = %d, h = %d\n", LRenderer->getWidth(), LRenderer->getHeight());
				SDL_RenderPresent(gRenderer);

#ifdef _WIN32
				Sleep(3000);
#else
				usleep(3000000);
#endif

				SDL_RenderClear(gRenderer);
			}

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				DRIVER_DIRECTION oldDirection = snake->m_CurDirection;

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							snake->changeDirection(UP);
							break;
						case SDLK_DOWN:
							snake->changeDirection(DOWN);
							break;
						case SDLK_LEFT:
							snake->changeDirection(LEFT);
							break;
						case SDLK_RIGHT:
							snake->changeDirection(RIGHT);
							break;
						case SDLK_q:
							quit = true;
							break;
						case SDLK_ESCAPE:
							quit = true;
							break;
						default:
							break;
						}
					}
				}

				//Avoid to turn around
				if (0 == (oldDirection + snake->m_CurDirection))
				{
					printf("Event queue lead to old direction opposite to new direction, fix it!\n");
					snake->m_CurDirection = oldDirection;
				}

				//Clear screen
				printf("Clear screen!\n");
				SDL_SetRenderDrawColor(gRenderer, 199, 237, 204, 0xFF);
				SDL_RenderClear(gRenderer);
				
				//Render red filled quad
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				//Generate food
				printf("Generate food!\n");
				bool bFoodOnSnake = false;
				do
				{
					if (food->beEaten || bFoodOnSnake)
						food->drawSelf();
					//Point to m_snake head
					SnakeList pFound = snake->m_snake;
					do
					{
						//Judge if food on snake
						if ((pFound->x_pos == food->m_x_pos) && (pFound->y_pos == food->m_y_pos))
						{
							printf("Food on snake\n");
							bFoodOnSnake = true;
							break;
						}
						else 
							bFoodOnSnake = false;
						
						pFound = pFound->next;
					} while (NULL != pFound);
				} while (bFoodOnSnake);
			
				food->beEaten = false;

				//Recover food
				if (NULL != food->m_sRec)
					SDL_RenderFillRect(gRenderer, &(food->m_sRec[0]));

				snake->moveSelf();
				snake->drawSelf();
				for (int i = 0; i < snake->m_iLength; i++)
				{
					//Render green filled quad
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
					if (0 == i)
						SDL_SetRenderDrawColor(gRenderer, 0xB2, 0x22, 0x22, 0xFF);
					SDL_RenderFillRect(gRenderer, &(snake->m_sRec[i])); 
					//Render blue outlined quad
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
					SDL_RenderDrawRect(gRenderer, &(snake->m_sRec[i]));
				}
				if (snake->m_snake->x_pos == food->m_x_pos && snake->m_snake->y_pos == food->m_y_pos)
				{
					snake->isEating = true;
					food->beEaten = true;
				}
				if (!snake->isAlive())
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					//Render text
					SDL_Color textColor = { 0, 0, 0, 0 };
					char sText[128] = "\0";
					snprintf(sText, sizeof(sText), "Game Over!You get %d.", snake->m_iLength - 2);
					printf("%s\n", sText);
 					if (LRenderer->loadFromRenderedText(gRenderer, gFont, sText, textColor))
 					{
						LRenderer->render(gRenderer, (SCREEN_WIDTH - LRenderer->getWidth()) / 2, (SCREEN_HEIGHT - LRenderer->getHeight()) / 2);
						printf("LRenderer: w = %d, h = %d\n", LRenderer->getWidth(), LRenderer->getHeight());
					}

					//Update screen
					SDL_RenderPresent(gRenderer);

					SDL_Event e;
					while (!quit)
					{
						while (0 != SDL_PollEvent(&e))
						{
							//User requests quit
							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							else if (e.type == SDL_KEYDOWN)
							{
								switch (e.key.keysym.sym)
								{
								case SDLK_q:
									quit = true;
									break;
								case SDLK_ESCAPE:
									quit = true;
									break;
								default:
									break;
								}
							}
						}
					}
				}

				//Update screen
				SDL_RenderPresent(gRenderer);

				printf("drag: %d\n", snake->m_drag);
#ifdef _WIN32
				Sleep((int)((snake->m_drag) / 1000));
#else
				usleep(snake->m_drag);
#endif


			}
		}
	}

	if (NULL != LRenderer)
	{
		LRenderer->Free();
		delete LRenderer;
		LRenderer = NULL;
	}
	
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

	closeAll();

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
		gWindow = SDL_CreateWindow("SDL2snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				}
			}

		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont(TTF_PATH, 28);
	if (NULL == gFont)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		gFont = TTF_OpenFont("lazy.ttf", 28);
		if (NULL == gFont)
		{
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			//For snap
			gFont = TTF_OpenFont("/snap/sdl2snake/current/usr/local/bin/lazy.ttf", 28);
			if (NULL == gFont)
			{
				printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}

	//Nothing to load
	return success;
}

void closeAll()
{
	//Destroy window
	if (NULL != gRenderer)
	{
		SDL_DestroyRenderer(gRenderer);
		gRenderer = NULL;
	}
	if (NULL != gWindow)
	{
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}

	//Free global font
	if (NULL != gFont)
	{
		TTF_CloseFont(gFont);
		TTF_Quit();
		gFont = NULL;
	}

	//Quit SDL subsystems
	SDL_Quit();
}
