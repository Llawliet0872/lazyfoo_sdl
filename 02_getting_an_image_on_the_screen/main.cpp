#include "../include/Log.hpp"

#define WIDTH 640
#define HEIGHT 480

SDL_Surface *surface = NULL;
SDL_Surface *helloWorld = NULL;
SDL_Window *window = NULL;

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

bool loadMedia()
{
	bool success = true;

	helloWorld = SDL_LoadBMP("hello_world.bmp");
	
	if(helloWorld == NULL)
	{
		utils::Log("failed to load image", true);
		success = false;
	}

	return success;
}

void close()
{
	SDL_FreeSurface(helloWorld);
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	utils::Log("Cleaned up");
}

int main()
{
	if(init())
	{
		surface = SDL_GetWindowSurface(window);
		loadMedia();

		SDL_BlitSurface(helloWorld, NULL, surface, NULL);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(3000);
	}

	close();

	return 0;
}
