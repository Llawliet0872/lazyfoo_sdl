#include <SDL2/SDL.h>
#include "../include/Log.hpp"
#include <thread>

#define WIDTH 640
#define HEIGHT 480

enum KeyPressSurface
{
	KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *keyPressSurface[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *currentSurface = NULL;

SDL_Surface *loadSurface(std::string path)
{
	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
	
	if(loadedSurface == NULL)
	{
		utils::Log("Unable to load image", true);
	}	

	return loadedSurface;
}

bool loadMedia()
{
	bool success = true;
	
	keyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if(keyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		utils::Log("Failed to load image", true);
		success = false;
	}

	keyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if(keyPressSurface[KEY_PRESS_SURFACE_UP] == NULL)
	{
		utils::Log("Failed to load image", true);
		success = false;
	}

	keyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if(keyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		utils::Log("Failed to load image", true);
		success = false;	
	}

	keyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if(keyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		utils::Log("Failed to load image", true);
		success = false;
	}

	keyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if(keyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL)
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

void close()
{
	SDL_FreeSurface(surface);
	SDL_FreeSurface(currentSurface);
	SDL_DestroyWindow(window);
}

int main()
{
	if(init())
	{
		surface = SDL_GetWindowSurface(window);
		bool running = true;
		SDL_Event e;
		loadMedia();
		currentSurface = keyPressSurface[KEY_PRESS_SURFACE_DEFAULT];

		while(running)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					running = false;
				}
				else if(e.type == SDL_KEYDOWN)
				{
					switch(e.key.keysym.sym)
					{
						case SDLK_UP:
							currentSurface = keyPressSurface[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							currentSurface = keyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							currentSurface = keyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							currentSurface = keyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							currentSurface = keyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
							break;
					}	
				}
			}

			SDL_BlitSurface(currentSurface, NULL, surface, NULL);
			SDL_UpdateWindowSurface(window);
		}
	}

	close();	

	return 0;
}
