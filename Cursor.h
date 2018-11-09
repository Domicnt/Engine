#include <SDL_image.h>
#include <SDL.h>
#undef main

#include "Collision.h"
#include <vector>
#pragma once

class Cursor {
	public:
		void mouseEvent(std::vector<Ball> &Balls, SDL_Event &e);

	private:

};