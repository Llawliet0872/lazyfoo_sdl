#include "../include/Log.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 640
#define HEIGHT 480

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

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
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

		void setColor(Uint8 r, Uint8 g, Uint8 b)
		{
			SDL_SetTextureColorMod(mTexture, r, g, b);
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

		void render(int x, int y, SDL_Rect *clip = NULL)
		{
			SDL_Rect renderQuad = {x, y, mWidth, mHeight};
			
			if(clip != NULL)
			{
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}
			
			SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
		}

		void setBlendMode(SDL_BlendMode blending)
		{
			SDL_SetTextureBlendMode(mTexture, blending);
		}

		void setAlpha(Uint8 a)
		{
			SDL_SetTextureAlphaMod(mTexture, a);
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

LTexture gSpriteSheetTexture;

bool loadMedia()
{
    bool success = true;

    if( !gSpriteSheetTexture.loadFromFile("foo.png"))
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        //Set sprite clips
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w =  64;
        gSpriteClips[ 0 ].h = 205;

        gSpriteClips[ 1 ].x =  64;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w =  64;
        gSpriteClips[ 1 ].h = 205;
        
        gSpriteClips[ 2 ].x = 128;
        gSpriteClips[ 2 ].y =   0;
        gSpriteClips[ 2 ].w =  64;
        gSpriteClips[ 2 ].h = 205;

        gSpriteClips[ 3 ].x = 196;
        gSpriteClips[ 3 ].y =   0;
        gSpriteClips[ 3 ].w =  64;
        gSpriteClips[ 3 ].h = 205;
    }
    
    return success;
}

int main()
{
	if(init())
	{
		SDL_Event e;
		bool running = true;
		int frames = 0;
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

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			SDL_Rect *currentClip = &gSpriteClips[frames / 4];
			gSpriteSheetTexture.render((WIDTH - currentClip->w) / 2, (HEIGHT - currentClip->h) / 2, currentClip);

			SDL_RenderPresent(renderer);
			++frames;
			if(frames / 4 >= WALKING_ANIMATION_FRAMES)
				frames = 0;
		}
	}
}
