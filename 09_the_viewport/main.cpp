#include "../include/Log.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
SDL_Texture *texture = NULL;

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

SDL_Texture *loadTexture(std::string path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface == NULL)
	{
		utils::Log("Failed to load image");
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == NULL)
		{
			utils::Log("Failed to create texture", true);
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int main()
{
	if(init())
	{
		bool running = true;
		SDL_Event e;
		texture = loadTexture("viewport.png");

		while(running)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					running = false;
				}
			}
			SDL_Rect topLeftViewport = {0, 0, WIDTH / 2, HEIGHT / 2};
			/*
			 Same As:
			 topLeftViewport.x = 0;
			 topLeftViewport.y = 0;
			 topLeftViewport.w = WIDTH / 2;
			 topLeftViewport.h = HEIGHT / 2;
			*/
			SDL_RenderSetViewport(renderer, &topLeftViewport);
			SDL_RenderCopy(renderer, texture, NULL, NULL);

			SDL_Rect topRightViewport = {WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2};
			SDL_RenderSetViewport(renderer, &topRightViewport);
			SDL_RenderCopy(renderer, texture, NULL, NULL);

			SDL_Rect bottomViewport = {0, HEIGHT / 2, WIDTH, HEIGHT / 2};
			SDL_RenderSetViewport (renderer, &bottomViewport);
			SDL_RenderCopy(renderer, texture, NULL, NULL);

			SDL_RenderPresent(renderer);
		}
	}

	return 0;
}
