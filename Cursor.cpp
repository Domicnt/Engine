#include <SDL_image.h>
#include <SDL.h>
#undef main

#include "Collision.h"
#include "Cursor.h"
#include "Initialize.h"
#include <vector>
#include <cstdio>
Initialize initialize1;
Collision collision2;

void Cursor::mouseEvent(std::vector<Ball> &Balls, SDL_Event &e) {
	SDL_GetMouseState(&mousePosX, &mousePosY);
	if (e.button.type == SDL_MOUSEBUTTONDOWN) {
		if (e.button.button == SDL_BUTTON_LEFT) {
			mouseButtonsHeld[0] = true;
			collision2.selectedBall = NULL;
			for (unsigned short int i = 0; i < Balls.size(); i++) {
				printf("hi");
				printf("\n\n%f\n", mousePosX);
				if (pow(mousePosX - Balls[i].posX, 2) + pow(mousePosY - Balls[i].posY, 2) < pow(Balls[i].radius, 2)) {
					printf("hecc");
					collision2.selectedBall = i;
					break;
				}
			}
		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {
			mouseButtonsHeld[1] = true;
			printf("There were %d balls.\n", Balls.size());
			Balls.clear();
		}
	} else if (e.button.type == SDL_MOUSEBUTTONDOWN) {
		collision2.selectedBall = NULL;
		mouseButtonsHeld[0] = false;
		mouseButtonsHeld[1] = false;
	}
}