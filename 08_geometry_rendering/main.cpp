#include "../include/Log.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init()
{
	bool success = true;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		utils::Log("Failed to initialize SDL2", true);
		success = false;
	}
	else
	{
		utils::Log("Initialized SDL2");
		if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			utils::Log("Failed to intialized SDL2_image");
			success = false;
		}
		else
		{
			window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
			if(window == NULL)
			{
				utils::Log("Failed to create window", true);
				success = false;
			}
			else
			{
				utils::Log("Created window");
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if(renderer == NULL)
				{
					utils::Log("Failed to create renderer");
					success = false;
				}
				else
				{
					utils::Log("Created renderer");
				}
			}
		}
	}

	return success;
}


int main()
{
	if(init())
	{
		SDL_Event e;
		bool running = true;
		while(running)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					running = false;
				}
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255 ,255);
			SDL_RenderClear(renderer);
			
			SDL_Rect fillRect = {WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &fillRect);

			SDL_Rect outlineRect = {WIDTH / 6, HEIGHT / 6, WIDTH * 2 / 3, HEIGHT * 2 / 3};
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(renderer, &outlineRect);

			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderDrawLine(renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);

			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			for(int i = 0; i < HEIGHT; i += 4)
			{
				SDL_RenderDrawPoint(renderer, WIDTH / 2, i);
			}

			SDL_RenderPresent(renderer);
		}
	}

	return 0;
}
