#include <SDL_image.h>
#include <SDL.h>
#undef main

#include "Collision.h"
#pragma once

class Move {

	int SCREEN_WIDTH = 640; //1280 by 720 is screen size for this laptop
	int SCREEN_HEIGHT = 360;

	public:

		void moveBall(Ball &a);

	private:

		float timescale;
 };