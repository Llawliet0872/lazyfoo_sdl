#include "../include/Log.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 640
#define HEIGHT 480

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

class LTexture
{
	public:
		LTexture()
		{
			mTexture = NULL;
			mWidth = 0;
			mHeight = 0;
		}

		~LTexture()
		{
			free();
		}

		bool loadFromFile(std::string path)
		{
			free();
			SDL_Texture *newTexture = NULL;
			SDL_Surface *loadedSurface = IMG_Load(path.c_str());
			if(loadedSurface == NULL)
			{
				std::cout << "Unable to load image" << IMG_GetError() << std::endl;
			}
			else
			{
				SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
				newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
				if(newTexture == NULL)
				{
					utils::Log("Failed to create texture", true);
				}
				else
				{
					mWidth = loadedSurface->w;
					mHeight = loadedSurface->h;
				}

				SDL_FreeSurface(loadedSurface);
			}

			mTexture = newTexture;
			
			return mTexture != NULL;
		}

		void free()
		{
			if(mTexture != NULL)
			{
				SDL_DestroyTexture(mTexture);
				mTexture = NULL;
				mWidth = 0;
				mHeight = 0;
			}
		}

		void render(int x, int y)
		{
			SDL_Rect renderQuad = {x, y, mWidth, mHeight};
			SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
		}

		int getWidth()
		{
			return mWidth;
		}

		int getHeight()
		{
			return mHeight;
		}

	private:
		SDL_Texture *mTexture;
		int mWidth;
		int mHeight;
};

LTexture fooTexture;
LTexture backgroundTexture;

bool loadMedia()
{
	bool success = true;
	if(!fooTexture.loadFromFile("foo.png"))
	{
		utils::Log("Failed to load image");
		success = false;
	}
	if(!backgroundTexture.loadFromFile("background.png"))
	{
		utils::Log("Failed to load image");
		success = false;
	}

	return success;
}

void close()
{
	fooTexture.free();
	backgroundTexture.free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

int main()
{
	if(init())
	{
		bool running = true;
		SDL_Event e;
		loadMedia();
		while(running)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
					running = false;
			}

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			backgroundTexture.render(0, 0);
			fooTexture.render(240, 190);

			SDL_RenderPresent(renderer);
		}
	}
	
	close();

	return 0;
}
