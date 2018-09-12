#include <SDL.h>
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

class Graphics {
	int scale;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Rect pixels[DISPLAY_WIDTH * DISPLAY_HEIGHT];
public:
	void init(void);
	void clean(void);
	void render(unsigned char* grid);
	void clear();
};

#endif // !GRAPHICS_H_
