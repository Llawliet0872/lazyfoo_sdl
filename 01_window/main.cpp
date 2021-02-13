#include "../include/Log.hpp"

#define WIDTH 800
#define HEIGHT 600

int main()
{
	SDL_Window *window = NULL; // Initializing a window
	SDL_Surface *surface = NULL; // Initializing a surface to display stuff on
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		utils::Log("Failed to initialize", true);
	}
	else
	{
		utils::Log("Initialized SDL2");

		window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN); // Creating a window
								// title            x                         y               w      h         flags
		if(window == NULL)
		{
			utils::Log("Failed to create window", true);
		}
		else
		{
			utils::Log("Created window");
			surface = SDL_GetWindowSurface(window); // Creating a surface for the window
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255)); // Painting the surface white 
			SDL_UpdateWindowSurface(window); // Updating the window

			SDL_Delay(3000); // A delay of 5 seconds before closing the window
		}
	}

	SDL_FreeSurface(surface); // Destroying the surface
	SDL_DestroyWindow(window); // Destroying the window
	SDL_Quit(); // Cleaning up
	
	utils::Log("Cleaned Up");

	return 0;
}
