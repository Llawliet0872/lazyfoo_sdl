#pragma once
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

namespace utils
{
	template<typename T>
	inline void Log(T message, bool is_error = false)
	{
		if(is_error)
		{
			cout << "[LOGGER] " << message << ", " << SDL_GetError() << endl;
		}
		else
		{
			cout << "[LOGGER] " << message << endl;
		}
	}
}
