#include <iostream>
#include "GameMan.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//this tutorial wont use pointers
/*
This is a tutorial based on gamedevelopment.tutsplus.com
Work in Progress
Everything in sdl2 folder is necessary to be with main.cpp
*/
SDL_Renderer* ren;
SDL_Window* win;
GameMan* gam;

int screenWidth = 700;
int screenHeight = 600;
//maps tiles of 50px will be 50 by 35x30

void init()
{
	//make the window
	win = SDL_CreateWindow("2D_plat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (win == NULL)
	{
		std::cout << "window creation failed" << std::endl;
	}
	else
	{
		//make the renderer
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

		if (ren == NULL)
		{
			std::cout << "renderer creation failed" << std::endl;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) &imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}

			//iconMake(win);//icon not created yet

			//mouse cursor vanisher
			SDL_ShowCursor(SDL_DISABLE);
			//SDL_SetRelativeMouseMode(SDL_TRUE); // this should lock the mouse in place

		}
	}
	//start audio capabilities
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	//open the font
	TTF_Init();
	//mainFont = TTF_OpenFont("assets/earwig.ttf", 30);
}


void fps_60()//keep the game running at a smooth 60fps
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	frameStart = SDL_GetTicks();

	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime)
	{
		SDL_Delay(frameDelay - frameTime); //get ttf to print fps at the top
	}
}

void clean()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	gam->~GameMan();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void game_loop()
{
	init();
	//instantiate
	gam = new GameMan();
	gam->Start(ren);

	while (gam->player->running)
	{
		fps_60();
		//draw map
		gam->player->practice_map->map_render(ren);
		//draw character
		gam->player->control_updater(ren);
		//render to window
		SDL_RenderPresent(ren);
		//clear
		SDL_RenderClear(ren);
	}
	clean();
}

int main(int argc, char * argv[])
{
	game_loop();
	return 0;
}