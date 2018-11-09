#include <SDL_image.h>
#include <SDL.h>
#undef main

#include <string>
#include <stdio.h>
#include "Collision.h"
#include "Draw.h"
using namespace std;

Draw::Draw() {
	Texture = nullptr;

	textureWidth = 0;
	textureHeight = 0;
}

void Draw::drawCircle(Ball a, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	int x = a.radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (a.radius << 1);

	while (x >= y) {
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) + x, (int)round(a.posY) - y);
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) + x, (int)round(a.posY) + y);
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) - x, (int)round(a.posY) - y);
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) - x, (int)round(a.posY) + y);
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) + y, (int)round(a.posY) - x);
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) + y, (int)round(a.posY) + x);
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) - y, (int)round(a.posY) - x);
		SDL_RenderDrawPoint(renderer, (int)round(a.posX) - y, (int)round(a.posY) + x);

		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0) {
			x--;
			dx += 2;
			err += dx - (a.radius << 1);
		}
	}
}

void Draw::drawLine(Line a, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, a.start.x, a.start.y, a.end.x, a.end.y);
}

void Draw::loadTexture(std::string path, SDL_Renderer* renderer) {
	free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	//Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	//Create texture from surface pixels
	Texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	//Get image dimensions
	textureWidth = loadedSurface->w;
	textureHeight = loadedSurface->h;

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
}

void Draw::free() {
	if (Texture != nullptr)
	{
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
		textureWidth = 0;
		textureHeight = 0;
	}
}

void Draw::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip) {
	//set rendering space
	SDL_Rect renderQuad = { x, y, textureWidth, textureHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, Texture, clip, &renderQuad, angle, center, flip);
}