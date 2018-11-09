#include <SDL_image.h>
#include <SDL.h>
#undef main

#include <string>
#include <stdio.h>
#include <ctime>
#include "Collision.h"
#include "Initialize.h"
#include "Draw.h"
#include "Move.h"
#include "Cursor.h"

Initialize initialize;
Draw draw;
Collision collision;
Move move;
Cursor cursor;

int main(int argc, char args[]) {
	initialize.init();

	int SCREEN_WIDTH = 640; //1280 by 720 is screen size for this laptop
	int SCREEN_HEIGHT = 360;

	SDL_Event e;

	std::vector<Ball> Balls;

	std::vector<Line> Lines;

	srand((unsigned)time(0));

	for (int i = 0; i < 5; i++) {
		initialize.createRandomBall(Balls);
		initialize.createRandomLine(Lines);
	}

	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				cursor.mouseEvent(Balls, e);
			}
		}
		SDL_SetRenderDrawColor(initialize.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(initialize.renderer);
		for (unsigned short int i = 0; i < Balls.size(); i++) {
			//collision.BallsvsBalls(Balls, i);
			collision.BallsvsEdges(Balls[i]);
			
			move.moveBall(Balls[i]);

			draw.drawCircle(Balls[i], initialize.renderer);
			for (unsigned short int a = 0; a < Lines.size(); a++) {
				//collision.BallvsLine(Balls[i], Lines[a]);

			}
		}
		for (unsigned short int i = 0; i < Lines.size(); i++) {
			draw.drawLine(Lines[i], initialize.renderer);
		}
		SDL_RenderPresent(initialize.renderer);
	}

	initialize.close();
	return 0;
} 