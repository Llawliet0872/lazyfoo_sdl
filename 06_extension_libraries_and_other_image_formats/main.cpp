#include "../include/Log.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Surface *surface = NULL;
SDL_Window *window = NULL;
SDL_Surface *pngSurface = NULL;

bool init()
{
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		utils::Log("Failed to initialize SDL2", true);
		success = false;
	}
	else
	{
		utils::Log("Initialized SDL2");
		window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		
		if(window == NULL)
		{
			utils::Log("Failed to create window", true);
			success = false;
		}
		else
		{
			utils::Log("Created window");
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) &imgFlags))
			{
				utils::Log("Failed to initialize SDL2_image", true);
			}
			else
			{
				surface = SDL_GetWindowSurface(window);
			}
		}
	}

	return success;
}

SDL_Surface *loadSurface(std::string path)
{
	SDL_Surface *optimizedSurface = NULL;
	
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface == NULL)
	{
		utils::Log("Failed to load image");
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, 0);
		if(optimizedSurface == NULL)
		{
			utils::Log("Failed to optimize");
		}
		
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int main()
{
	if(init())
	{
		bool running = true;
		SDL_Event e;

		pngSurface = loadSurface("loaded.png");
		
		SDL_Rect stretchRect = {0, 0, WIDTH, HEIGHT};
		
		while(running)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					running = false;
				}
			}

			SDL_BlitScaled(pngSurface, NULL, surface, &stretchRect);
			SDL_UpdateWindowSurface(window);
		}	
	}

	return 0;
}
