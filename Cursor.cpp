#include <SDL_image.h>
#include <SDL.h>
#undef main

#include "Collision.h"
#include "Cursor.h"
#include "Initialize.h"
#include <vector>
#include <cstdio>
Initialize initialize1;

void Cursor::mouseEvent(std::vector<Ball> &Balls, SDL_Event &e) {
	if (e.button.button == SDL_BUTTON_LEFT) {
		for (int i = 0; i < 5; i++) {
			initialize1.createRandomBall(Balls);
		}
	} else if (e.button.button == SDL_BUTTON_RIGHT) {
		printf("There were %d balls.\n", Balls.size());
		Balls.clear();
	}
}