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
