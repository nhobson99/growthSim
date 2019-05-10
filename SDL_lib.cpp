SDL_Renderer 	* gRenderer = NULL;
SDL_Window 	* gWindow = NULL;

bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("SDL couldn't initialize");
		return false;
	}


	gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	return true;
}


//Point class for doing 2D maths
class Point {
	public:
		int x;
		int y;
		Point rotate(double angle);
		Point operator +(class Point p);

		Point();
		Point(int X, int Y);
};

Point::Point() {
	x = 0;
	y = 0;

	return;
}

vector <char> color (int hex) {
	int r, g, b;
	r = (hex >> 16) & 0xff;
	g = (hex >> 8) 	& 0xff;
	b = (hex) 	& 0xff;

	vector <char> color;
	color.push_back(r);
	color.push_back(g);
	color.push_back(b);

	return color;
}

vector <char> buddy_color = color(0xee5d6c);
vector <char> hex_color	  = color(0xeeaf61);
vector <char> bg_color	  = color(0x000000);

Point::Point(int X, int Y) {
	x = X;
	y = Y;

	return;
}

class Board {
	public:
		bool processEvents();
		void gameloop();
		void render();
		void close();
		void restart();
		Board();
	private:
		vector <class Buddy> buddies;
};

const int SCREEN_W = 500;
const int SCREEN_H = 500;

//Adds two points
Point Point::operator +(class Point p) {
	Point rv;
	rv.x = x + p.x;
	rv.y = y + p.y;

	return rv;
}

Point Point::rotate(double angle) {
	Point rv;
	double radius;
	double curAngle;

	radius = sqrt((double)x*x + (double)y*y);
	curAngle = atan((double)y / (double)x);

	if (x >= 0 and y < 0) {
		curAngle = -curAngle;
	} else if (x < 0 and y >= 0) {
		curAngle = PI - curAngle;
	} else if (x < 0 and y < 0) {
		curAngle = PI + curAngle;
	}

	rv.x = radius*cos(angle + curAngle);
	rv.y = radius*sin(angle + curAngle);

	return rv;
}

//Draws a 1 px thick line from point p1 to point p2
void drawLine(Point p1, Point p2, SDL_Renderer * gRenderer, vector <char> & color) {
	SDL_SetRenderDrawColor(gRenderer, color[0], color[1], color[2], 255);
	SDL_RenderDrawLine(gRenderer, p1.x, p1.y, p2.x, p2.y);

	return;
}

vector <Point> buddyPoints;

Board::Board() {
	if (init()) {
		Buddy b;
		b.xPos = 0;
		b.yPos = 0;

		buddies.push_back(b);

		gameloop();
	}
}

//Contains the main loop for the game
void Board::gameloop(){
	while (not quit) {
		//get events (inputs, x button, etc)
		processEvents();
		render();
	}

	close();
}


//Handles event processing
bool Board::processEvents(){
	//get events (inputs, x button, etc)
	//
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0){
		if (e.type == SDL_QUIT){
			quit = true;
			return false;
		}
		if (e.type == SDL_KEYDOWN){
			switch (e.key.keysym.sym){
				default:
					break;
			}
		} else if (e.type == SDL_KEYUP){
			switch (e.key.keysym.sym){
				case 'q':
					printf("Quitting\n");
					quit = true;
					return false;
			}
		}
	}

	return true;
}

//Draws and animates board
void Board::render(){
	int centerx = SCREEN_W / 2;
	int centery = SCREEN_H / 2;

	SDL_SetRenderDrawColor(gRenderer, bg_color[0], bg_color[1], bg_color[2], 255);
	SDL_RenderClear(gRenderer);

	//Update the window when all done
	//SDL_UpdateWindowSurface(gWindow);
	
	for (int i = 0; i < buddies.size(); i++) {
		Point target = buddies[i].findFood();
		buddies[i].goToTarget(target);
		printf("Buddy: %d %d\n", buddies[i].xPos, buddies[i].yPos);
		buddies[i].Draw(gRenderer);
	}

	SDL_RenderPresent(gRenderer);
}

void Board::close(){
	printf("Closing...\n");
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

void Board::restart(){
	SDL_SetRenderDrawColor(gRenderer, bg_color[0], bg_color[1], bg_color[2], 255);
	SDL_RenderClear(gRenderer);
	SDL_RenderPresent(gRenderer);
}	


