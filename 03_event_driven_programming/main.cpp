#include "../include/Log.hpp"
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Surface *xSurface = NULL;
SDL_Surface *surface = NULL;

bool loadMedia()
{
	bool success = true;

    xSurface = SDL_LoadBMP("x.bmp");

    if(xSurface == NULL)
    {
        utils::Log("Failed to load image", true);
    	success = false;
	}

	return success;
}

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
		}
	}

	return success;
}

int main()
{
    if(init())
    {
        bool quit = false;
        surface = SDL_GetWindowSurface(window);
		loadMedia();
        SDL_Event e;

        while(!quit)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            SDL_BlitSurface(xSurface, NULL, surface, NULL);

            SDL_UpdateWindowSurface(window);
        }
    }

    SDL_FreeSurface(xSurface);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
