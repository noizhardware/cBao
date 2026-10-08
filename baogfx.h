#ifndef _BAOGFX_H_
#define _BAOGFX_H_

#define BAOGFX_H_CREATED "2026i24-1501"
#define BAOGFX_H_VERSION "2026j04-2327"

/*** TODO

*/
/*** DOCU
	- sudo apt install libsdl2-dev
	- needs C99
	- gcc -std=c99 src.c -o output $(sdl2-config --cflags --libs) && ./output
*/

/*** DEFINES */
	#define BAOGFX_FRAMELEN_STATIC 200 /* for static renders */
	
	#ifdef BAOGFX_FULLSCREEN
		#define BAOGFX_CREATEWIN \
			win = SDL_CreateWindow(GC_WINNAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displayX, displayY, 0);\
			SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP)
	#else
		#define BAOGFX_CREATEWIN \
			win = SDL_CreateWindow(GC_WINNAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GC_WINX_SIZE, GC_WINY_SIZE, 0)
	#endif

	#define BAOGFX_FAST_PRE \
		SDL_Window* win;\
		SDL_Renderer* ren;\
		SDL_Event ev;\
		int running;\
		SDL_Init(SDL_INIT_VIDEO);\
		SDL_ShowCursor(SDL_DISABLE);/*hide mouse cursor/pointer*/\
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");/*forces nearest-neighbor to get sharp blocks instead of a blurred upscale*/\
		SDL_DisplayMode desktopMode;\
		SDL_GetDesktopDisplayMode(0, &desktopMode);\
		int displayX = desktopMode.w;\
		int displayY = desktopMode.h;\
		int resX = desktopMode.w/BAOGFX_RESDOWNSCALE;\
		int resY = desktopMode.h/BAOGFX_RESDOWNSCALE;\
		SDL_Log("display size(xy); %d x %d\n", displayX, displayY);\
		SDL_Log("resize[/%d] -> %d x %d\n", BAOGFX_RESDOWNSCALE, resX, resY);\
		BAOGFX_CREATEWIN;\
		ren = SDL_CreateRenderer(win, -1, 0);\
		SDL_RenderSetLogicalSize(ren, resX, resY);\
		SDL_RenderSetIntegerScale(ren, SDL_TRUE);\
		running = 1;\
		while (running) {\
		while (SDL_PollEvent(&ev)) {\
		if (ev.type == SDL_QUIT) {\
		running = 0;}}\

	#define BAOGFX_FAST_POST \
		SDL_RenderPresent(ren);\
		SDL_Delay(BAOGFX_FRAMELEN);\
		}\
		SDL_DestroyRenderer(ren);\
		SDL_DestroyWindow(win);\
		SDL_Quit()

	#define BAOGFX_STATIC_PRE \
		SDL_Window* win;\
		SDL_Renderer* ren;\
		SDL_Event ev;\
		int running;\
		SDL_Init(SDL_INIT_VIDEO);\
		if(BAOGFX_MOUSEOFF){SDL_ShowCursor(SDL_DISABLE);}/*hide mouse cursor/pointer*/\
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");/*forces nearest-neighbor so you get sharp blocks instead of a blurred upscale*/\
		SDL_DisplayMode desktopMode;\
		SDL_GetDesktopDisplayMode(0, &desktopMode);\
		int displayX = desktopMode.w;\
		int displayY = desktopMode.h;\
		int resX = desktopMode.w/BAOGFX_RESDOWNSCALE;\
		int resY = desktopMode.h/BAOGFX_RESDOWNSCALE;\
		SDL_Log("display size(xy); %d x %d\n", displayX, displayY);\
		SDL_Log("resize[/%d] -> %d x %d\n", BAOGFX_RESDOWNSCALE, resX, resY);\
		BAOGFX_CREATEWIN;\
		ren = SDL_CreateRenderer(win, -1, 0);\
		SDL_RenderSetLogicalSize(ren, resX, resY);\
		SDL_RenderSetIntegerScale(ren, SDL_TRUE)

	#define BAOGFX_STATIC_POST \
		SDL_RenderPresent(ren);\
		running = 1;\
		while (running) {\
		while (SDL_PollEvent(&ev)) {\
		if (ev.type == SDL_QUIT) {running = 0;}\
		if(ev.type==SDL_KEYDOWN && !ev.key.repeat){\
			SDL_Keycode k = ev.key.keysym.sym;\
			if(k==SDLK_ESCAPE) { running=0; }\
		}\
		}\
		SDL_Delay(BAOGFX_FRAMELEN_STATIC);\
		}\
		SDL_DestroyRenderer(ren);\
		SDL_DestroyWindow(win);\
		SDL_Quit()
/* DEFINES end. */

/*** INCLUDES */
	#include <SDL2/SDL.h>
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** TYPEDEFS */
	typedef struct color_t_{
		Uint8 r;
		Uint8 g;
		Uint8 b;
	} color_t;
/* TYPEDEFS end. */

/*** GLOBALS */
	const color_t GC_colorBlack = {0, 0, 0};
	const color_t GC_colorTermBlackYel = {28, 17, 8};
	const color_t GC_colorTermAmber = {254, 200, 69};
	const color_t GC_colorWhite = {255, 255, 255};
	const color_t GC_colorNUcalPink = {236, 36, 99};
	const color_t GC_colorMclarenOrange = {245, 111, 35};
	const color_t GC_colorMclarenBlack = {36, 32, 30};
	const color_t GC_colorMclarenWhite = {224, 223, 231};
	const color_t GC_colorMclarenRed = {118, 26, 8};
	const color_t GC_colorMclarenGrey = {115, 122, 116};
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	void drawBg(color_t col, SDL_Renderer* ren);
	void drawPoint(int x, int y, color_t col, SDL_Renderer* ren);
	void drawLine(int x1, int y1, int x2, int y2, color_t col, SDL_Renderer* ren);
	void drawSquare(int posx, int posy, int size, color_t col, SDL_Renderer* ren);
	void drawSquareFromCenter(int posx, int posy, int size, color_t col, SDL_Renderer* ren);
	void drawCircle(int centerX, int centerY, int radius, color_t col, SDL_Renderer* ren);
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
	void drawPoint(int x, int y, color_t col, SDL_Renderer* ren){
		SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
		SDL_RenderDrawPoint(ren, x, y);
		return;
	}
	void drawBg(color_t col, SDL_Renderer* ren){
		SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
		SDL_RenderClear(ren);
		return;
	}
	void drawLine(int x1, int y1, int x2, int y2, color_t col, SDL_Renderer* ren){
		SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
		SDL_RenderDrawLine(ren, x1, y1, x2, y2);
		return;
	}
	void drawSquare(int posx, int posy, int size, color_t col, SDL_Renderer* ren){
		SDL_Rect square = {posx, posy, size, size};
		SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
		SDL_RenderDrawRect(ren, &square);
		return;
	}
	void drawSquareFromCenter(int posx, int posy, int size, color_t col, SDL_Renderer* ren){
		SDL_Rect square = {posx-size, posy-size, size, size};
		SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
		SDL_RenderDrawRect(ren, &square);
		return;
	}
	void drawCircle(int centerX, int centerY, int radius, color_t col, SDL_Renderer* ren){
		const int32_t diameter = (radius * 2);
		int32_t x = (radius - 1);
		int32_t y = 0;
		int32_t tx = 1;
		int32_t ty = 1;
		int32_t error = (tx - diameter);

		SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
		while (x >= y){
			/* Each of the following renders an octant of the circle */
			SDL_RenderDrawPoint(ren, centerX + x, centerY - y);
			SDL_RenderDrawPoint(ren, centerX + x, centerY + y);
			SDL_RenderDrawPoint(ren, centerX - x, centerY - y);
			SDL_RenderDrawPoint(ren, centerX - x, centerY + y);
			SDL_RenderDrawPoint(ren, centerX + y, centerY - x);
			SDL_RenderDrawPoint(ren, centerX + y, centerY + x);
			SDL_RenderDrawPoint(ren, centerX - y, centerY - x);
			SDL_RenderDrawPoint(ren, centerX - y, centerY + x);

			if (error <= 0){
				++y;
				error += ty;
				ty += 2;
			}
			if (error > 0){
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
		return;
	}
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _BAOGFX_H_ */
