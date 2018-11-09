#include <SDL_image.h>
#include <SDL.h>
#undef main

#include "Collision.h"
#include <vector>
#pragma once

class Initialize {

	public:
		void init();
		void close();

		int SCREEN_WIDTH = 640; //1280 by 720 is screen size for this laptop
		int SCREEN_HEIGHT = 360;

		SDL_Window* window = nullptr;

		SDL_Renderer* renderer = nullptr;

		void createBall(std::vector<Ball> &Balls, int radius, float posX, float posY, float velX, float velY, int mass);
		void createRandomBall(std::vector<Ball> &Balls);

		void createLine(std::vector<Line> &Lines, int startX, int startY, int endX, int endY);
		void createRandomLine(std::vector<Line> & Lines);

	private:

};