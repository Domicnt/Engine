#include <SDL_image.h>
#include <SDL.h>
#undef main

#include <stdio.h>
#include <vector>
#include "Collision.h"
using namespace std;

void Collision::BallsvsBalls(std::vector<Ball> &Balls, int a) {
	int r;
	int distance;
	for (short unsigned int b = a + 1; b < Balls.size(); b++) {
		distance = (int)round(sqrt(pow((Balls[b].posX - Balls[a].posX), 2) + pow((Balls[b].posY - Balls[a].posY), 2)));
		r = (int)round(Balls[a].radius + Balls[b].radius);
		if (r >= distance) {
			//actual formula is v2 = v1 - 2n * (v1 * n)
			// in which v2 is the resulting vector, v1 is the starting vector,
			//n is the normal line of the wall, which should be normalized,
			//and v1 * n is the dot product of v1 and n
			
			int xChange = 0.5 * (distance - r) * (Balls[a].posX - Balls[b].posX) / distance;
			int yChange = 0.5 * (distance - r) * (Balls[a].posX - Balls[b].posX) / distance;
			
			Balls[a].posX -= xChange;
			Balls[a].posY -= yChange;
			Balls[b].posX += xChange;
			Balls[b].posY += yChange;

			Balls[a].velocity.x *= -1;
			Balls[a].velocity.y *= -1;
			Balls[b].velocity.x *= -1;
			Balls[b].velocity.y *= -1;
		}
	}
}

void Collision::BallsvsEdges(Ball &a) {
	if (a.posX + a.radius >= SCREEN_WIDTH) {
		a.posX = (float)round(SCREEN_WIDTH - a.radius);
		a.velocity.x *= -a.restitution;
		a.velocity.y *= .75;
	} else if (a.posX - a.radius <= 0) {
		a.posX = (float)round(a.radius);
		a.velocity.x *= -a.restitution;
		a.velocity.y *= .75;
	}
	if (a.posY + a.radius >= SCREEN_HEIGHT) {
		a.posY = (float)round(SCREEN_HEIGHT - a.radius);
		a.velocity.y *= -a.restitution;
		a.velocity.x *= .75;
	} else if (a.posY - a.radius <= 0) {
		a.posY = (float)round(a.radius );
		a.velocity.y *= -a.restitution;
		a.velocity.x *= .75;
	}
}

void Collision::BallvsLine(Ball &a, Line &b) {
	float t = ((a.posY - b.start.y) * (b.end.y - b.start.y) + (a.posX - b.start.x) * (b.end.x - b.start.x)) /
		(pow((b.end.y - b.start.y), 2) + pow((b.end.x - b.start.x), 2));

	float projectedX = b.start.x + t * (b.end.x - b.start.x);
	float projectedY = b.start.y + t * (b.end.y - b.start.y);

	float distance = sqrt(pow((a.posX - projectedX), 2) + pow((a.posY - projectedY), 2));

	// if the circle is touching the line
	if (distance <= a.radius && ((projectedX <= b.end.x && projectedY - a.radius <= b.end.y) && (projectedX >= b.start.x && projectedY + a.radius >= b.start.y)) || ((projectedX >= b.end.x && projectedY + a.radius >= b.end.y) && (projectedX <= b.start.x && projectedY - a.radius <= b.start.y))) {
		printf("Collision Detected\n");
		a.posX -= a.velocity.x;
		a.posY -= a.velocity.y;

		float angle = atan(a.velocity.y / a.velocity.x) * 180 / 3.141592;
		printf("Angle: %f\n", angle);

		double magnitude = sqrt(pow((b.start.y - b.end.y), 2) + pow((b.start.x - b.end.x), 2));
		//double vectorX = abs(b.start.x - b.end.x) / magnitude;
		//double vectorY = abs(b.start.y - b.end.y) / magnitude;

		double norm = 1 / (((b.start.y - b.end.y) / (b.start.x - b.end.x)) / magnitude);
		printf("Norm: %f\n", norm);

		a.velocity.x = -(2 * (norm * a.velocity.x) * (norm - a.velocity.x));
		printf("X axis Velocity: %lf, ", a.velocity.x);
		a.velocity.y = -(2 * (norm * a.velocity.y) * (norm - a.velocity.y));
		printf("Y axis Velocity: %lf\n", a.velocity.y);

	}
}