#include <SDL_image.h>
#include <SDL.h>
#undef main

#include <string>
#include <stdio.h>
#include <vector>
#include <ctime>
#include "Initialize.h"
#include "Collision.h"
#include "Draw.h"

Draw draw1;

void Initialize::init() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//Create window
	window = SDL_CreateWindow("SDL Testing things", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create vsynced renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	(IMG_Init(imgFlags) & imgFlags);
}

void Initialize::close() {
	draw1.free();

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Initialize::createBall(std::vector<Ball> &Balls, int radius, float posX, float posY, float velX, float velY, int mass) {
	Ball newBall;
	newBall.radius = radius;
	newBall.posX = posX;
	newBall.posY = posY;
	newBall.velocity.x = velX;
	newBall.velocity.y = velY;
	newBall.mass = mass;

	Balls.push_back(newBall);
}

void Initialize::createRandomBall(std::vector<Ball> &Balls) {
	Ball newBall;
	bool acceptableLocation = false;

	while (acceptableLocation == false) {

		newBall.radius = 5 + (rand() % 45) + 1;
		newBall.posX = (float)round(newBall.radius + (rand() % SCREEN_WIDTH - 2 * newBall.radius) + 1);
		newBall.posY = (float)round(newBall.radius + (rand() % SCREEN_HEIGHT - 2 * newBall.radius) + 1);
		if (Balls.size() != 0) {
			for (unsigned short int i = 0; i < Balls.size(); i++) {
				float distance = (float)round(pow((Balls[i].posX - newBall.posX), 2) + pow((Balls[i].posY - newBall.posY), 2));
				float r = (float)round(pow(newBall.radius + Balls[i].radius, 2));
				printf("Distance: %f\n", distance);
				printf("R: %f\n", r);
				printf("There are now: %d Balls\n\n", Balls.size() + 1);
				if (r <= distance) {
					acceptableLocation = true;
				}
			}
		} else if (Balls.size() == 0) {
			acceptableLocation = true;
		}   
	}
	newBall.velocity.x = (float)round((rand() % 20) + 1) - 10;
	newBall.velocity.y = (float)round((rand() % 20) + 1) - 10;
	newBall.mass = 10;
	newBall.restitution = .75;
	
	Balls.push_back(newBall);
}

void Initialize::createLine(std::vector<Line> &Lines, int startX, int startY, int endX, int endY) {
	Line newLine;

	newLine.start.x = startX;
	newLine.start.y = startY;

	newLine.end.x = endX;
	newLine.end.y = endY;

	newLine.angle = (float)round(atan(newLine.end.y - newLine.start.y / newLine.end.x - newLine.start.x));

	Lines.push_back(newLine);
}

void Initialize::createRandomLine(std::vector<Line> & Lines) {
	Line newLine;

	newLine.start.x = (rand() % SCREEN_WIDTH) + 1;
	newLine.start.y = (rand() % SCREEN_HEIGHT) + 1;

	newLine.end.x = (rand() % SCREEN_WIDTH) + 1;
	newLine.end.y = (rand() % SCREEN_HEIGHT) + 1;

	newLine.angle = (float)round(atan(newLine.end.y - newLine.start.y / newLine.end.x - newLine.start.x));

	Lines.push_back(newLine);
}