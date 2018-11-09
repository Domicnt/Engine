#include <SDL_image.h>
#include <SDL.h>
#undef main

#include "Collision.h"
#include "Cursor.h"
#include "Initialize.h"
#include <vector>
Initialize initialize1;

void Cursor::mouseEvent(std::vector<Ball> &Balls, SDL_Event &e) {
	if (e.button.button == SDL_BUTTON_LEFT) {
		initialize1.createRandomBall(Balls);
	} else if (e.button.button == SDL_BUTTON_RIGHT) {
		Balls.clear();
	}
}