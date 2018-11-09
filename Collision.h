#include <SDL_image.h>
#include <SDL.h>
#undef main

#include <vector>
#pragma once

struct Vector {
	float angle;// = atan(y/x);
	float magnitude;// = sqrt(pow(x, 2) + pow(y, 2));

	float x;
	float y;
};

struct Ball {
	int radius;

	float posX;
	float posY;

	Vector velocity;

	int mass;
	float restitution;
};

struct Line {
	SDL_Point start;
	SDL_Point end;

	float angle;
};

class Collision{

	public:
		std::vector<bool> collidingBalls;

		void BallsvsBalls(std::vector<Ball> &Balls, int a);

		void BallsvsEdges(Ball &a);

		void BallvsLine(Ball &a, Line &b);

		//bool onGround(Ball &a);

		float restitution;

		int maxSpeed = 10;

		int SCREEN_WIDTH = 640; //1280 by 720 is screen size for this laptop
		int SCREEN_HEIGHT = 360;
};
