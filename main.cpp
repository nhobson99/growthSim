#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

using namespace std;

#define _USE_MATH_DEFINES

const double PI = M_PI;
bool quit = false;

class Buddy {
	public:
		void Draw(SDL_Renderer * gRenderer);
		Point findFood();
		void goToTarget(Point p);
		
		int xPos;
		int yPos;
		double angle;
};

void Buddy::Draw(SDL_Renderer * gRenderer) {
	Point p1, p2;

	int centerx, centery;
	centerx = SCREEN_W/2 + xPos;
	centery = SCREEN_H/2 + yPos;

	Point center(centerx, centery);

	for (int i = 0; i < buddyPoints.size() - 1; i++) {
		p1 = buddyPoints[i].rotate(angle - PI/2) + center;
		p2 = buddyPoints[i+1].rotate(angle - PI/2) + center;

		drawLine(p1, p2, gRenderer, buddy_color);
	}

	return;
}

//Tries to find the nearest food (center otherwise)
Point Buddy::findFood() {
	return Point(120, -90);
}

//Goes to a point in 2D space
void Buddy::goToTarget(Point p) {
	if (p.x > xPos) xPos += 1;
	if (p.x < xPos) xPos -= 1;
	if (p.y > yPos) yPos += 1;
	if (p.y < yPos) yPos -= 1;

	return;
}
int main(){
	srand(time(NULL));

	buddyPoints.push_back(Point(0, 10));
	buddyPoints.push_back(Point(8, 0));
	buddyPoints.push_back(Point(3, 0));
	buddyPoints.push_back(Point(0, 2));
	buddyPoints.push_back(Point(-3, 0));
	buddyPoints.push_back(Point(-8, 0));
	buddyPoints.push_back(Point(0, 10));

	Board myBoard = Board();

	return 0;
}
