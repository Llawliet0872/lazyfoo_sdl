#include "../include/Log.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
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

bool loadMedia()
{
	bool success = true;
	texture = loadTexture("texture.png");
	if(texture == NULL)
	{
		utils::Log("Failed to load texture");
		success = false;
	}

	return success;
}

void close()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
	IMG_Quit();
	utils::Log("Cleaned up");
}

int main()
{
	if(init())
	{
		SDL_Event e;
		bool running = true;
		loadMedia();

		while(running)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					running = false;
				}
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
	}
	close();

	return 0;
}
