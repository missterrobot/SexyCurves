/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_syswm.h>
#include <Windows.h>
#include <conio.h>

// Get resolution of primary monitor
int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void FillInsideCircle(SDL_Renderer* renderer, int w, int h, int w10, int h10) {
	//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	//topLeft
	SDL_Rect rect1 = { 3, 3 , 10, 10 };
	SDL_Rect rect2 = { 6, 1 , 10, 10 };
	SDL_Rect rect3 = { 1, 6 , 10, 10 };
	SDL_RenderDrawLine(renderer,8, 0, 9, 0);
	SDL_RenderDrawLine(renderer, 0, 8, 0, 9);

	//topRight
	SDL_Rect rect7 = { w-13, 3 , 10, 10 };
	SDL_Rect rect8 = { w-15, 1 , 10, 10 };
	SDL_Rect rect9 = { w-11, 6 , 10, 10 };
	SDL_RenderDrawLine(renderer, w-8, 0, w-9, 0);
	SDL_RenderDrawLine(renderer, 0, h-8, 0, h-9);

	//bottomLeft
	SDL_Rect rect4 = { 3, h-12 , 10, 10 };
	SDL_Rect rect5 = { 6, h-10 , 10, 10 };
	SDL_Rect rect6 = { 1, h-15 , 10, 10 };
	SDL_RenderDrawLine(renderer, 0, h-9, 0, h-10);

	//bottom right THIS IS GOOD FIRST SQUARE
	SDL_Rect rect10 = { w-12, h - 12 , 10, 10 };
	SDL_Rect rect11 = { w-15, h-9 , 10, 10 };
	SDL_Rect rect12 = { w-9, h-15 , 10, 10 };

	SDL_RenderFillRect(renderer, &rect1);
	SDL_RenderFillRect(renderer, &rect2);
	SDL_RenderFillRect(renderer, &rect3);
	SDL_RenderFillRect(renderer, &rect4);
	SDL_RenderFillRect(renderer, &rect5);
	SDL_RenderFillRect(renderer, &rect6);
	SDL_RenderFillRect(renderer, &rect7);
	SDL_RenderFillRect(renderer, &rect8);
	SDL_RenderFillRect(renderer, &rect9);
	SDL_RenderFillRect(renderer, &rect10);
	SDL_RenderFillRect(renderer, &rect11);
	SDL_RenderFillRect(renderer, &rect12);
}

void FillCircle(SDL_Renderer* renderer, int width, int height) {

	/*
	SDL_Rect rect1 = { 3, 3, 10, 10 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rect1);
	SDL_Rect rect2 = { 6, 1, 10, 10 };
	SDL_RenderFillRect(renderer, &rect2);
	SDL_Rect rect3 = { 1, 6, 10, 10 };
	SDL_RenderFillRect(renderer, &rect3);
	SDL_Rect rect4 = { 0, 8, 10, 10 };
	SDL_RenderFillRect(renderer, &rect4);
	SDL_Rect rect5 = { 8, 0, 10, 10 };
	SDL_RenderFillRect(renderer, &rect5);*/
	int w10 = width - 10;
	int h10 = height - 10;

	//Draws black on all 4 corners
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//sets draw color to black
	SDL_Rect rect1 = { 0, 0, 10, 10 };
	SDL_Rect rect2 = { 0, h10, 10, 10 };
	SDL_Rect rect3 = { w10, 0, 10, 10 };
	SDL_Rect rect4 = { w10, h10, 10, 10 };
	SDL_RenderFillRect(renderer, &rect1);
	SDL_RenderFillRect(renderer, &rect2);
	SDL_RenderFillRect(renderer, &rect3);
	SDL_RenderFillRect(renderer, &rect4);

	
	//draws circles in all 4 corners
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);//sets draw color to magenta
	DrawCircle(renderer, 10, 10, 10);
	DrawCircle(renderer, 10, h10-1, 10);
	DrawCircle(renderer, w10-1, 10, 10);
	DrawCircle(renderer, width - 10, height - 10, 10);

	//fills all 4 corner curves (very inefficeint!!)
	FillInsideCircle(renderer, width, height, w10, h10);
}

// Makes a window transparent by setting a transparency color.
bool MakeWindowTransparent(SDL_Window* window, COLORREF colorKey) {
	// Get window handle (https://stackoverflow.com/a/24118145/3357935)
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
	SDL_GetWindowWMInfo(window, &wmInfo);
	HWND hWnd = wmInfo.info.win.window;

	// Change window type to layered (https://stackoverflow.com/a/3970218/3357935)
	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Set transparency color
	return SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}

void drawCorners(SDL_Renderer* renderer, int width, int height, int round){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect rect1 = { 0,0,round,round };
	SDL_Rect rect2 = { 0,height-round,round,round };
	SDL_Rect rect3 = { width-round,0,round,round };
	SDL_Rect rect4 = { width-round,height-round,round,round };
	SDL_RenderFillRect(renderer, &rect1);
	SDL_RenderFillRect(renderer, &rect2);
	SDL_RenderFillRect(renderer, &rect3);
	SDL_RenderFillRect(renderer, &rect4);
}

int yCoords[10] = { 8, 6, 4, 3, 2, 2, 1, 1, 0, 0 };


void roundLeft(SDL_Renderer* renderer, int width, int height, int round) {
	for (int x = 0; x < round; x++) {
			//SDL_RenderDrawLine(renderer, x, round - x, x, height - round + x);
		SDL_RenderDrawLine(renderer, x, yCoords[x], x, height-yCoords[x]);
	}
}

void roundRight(SDL_Renderer* renderer, int width, int height, int round) {
	for (int x = -1; x < round; x++) {
		//SDL_RenderDrawLine(renderer, width-round+x, x, width - round + x, height - x);
		SDL_RenderDrawLine(renderer, width - round + x, yCoords[round-x]-1, width - round + x, height - yCoords[round-x]);
	}
}

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//combine flags
		Uint32 flags = SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS | SDL_WINDOW_SKIP_TASKBAR;

		window = SDL_CreateWindow("SDL Transparent Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,desktopWidth, desktopHeight, flags);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			// Set background color to magenta and clear screen
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			SDL_RenderClear(renderer);

			int round = 10;//Amount of pixels to round by

			drawCorners(renderer, desktopWidth, desktopHeight, round);
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			roundLeft(renderer, desktopWidth, desktopHeight, round);
			roundRight(renderer, desktopWidth, desktopHeight, round);
			 
			//Update the screen with any new rendering
			SDL_RenderPresent(renderer);

			// Add window transparency (Magenta will be see-through)
			MakeWindowTransparent(window, RGB(255, 0, 255));
			
			char input;
			printf("Press any key to quit\n");
			input = _getch();
			//Wait
			//SDL_Delay( 5000000 );
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}