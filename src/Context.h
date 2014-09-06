#pragma once

#include <SDL2/SDL.h>

class Context {
public:
	Context(unsigned width, unsigned height)
	: window(nullptr)
	, renderer(nullptr)
	, valid(false) {

		SDL_Init(SDL_INIT_VIDEO);
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetSwapInterval(1);

		window = SDL_CreateWindow("sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		context = SDL_GL_CreateContext(window);
		renderer = SDL_CreateRenderer(window, GetGLRenderer(window), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
		if (!window || !context || !renderer) {
			return;
		}
		
		valid = true;
	}
	
	~Context() {
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	void Present() {
		SDL_RenderPresent(renderer);		
	}
	
	bool IsValid() {
		return valid;
	}
	
	unsigned GetWidht() {
		SDL_DisplayMode display;
		SDL_GetWindowDisplayMode(window, &display);
		return display.w;
	}

	unsigned GetHeight() {
		SDL_DisplayMode display;
		SDL_GetWindowDisplayMode(window, &display);
		return display.h;
	}
	
private:
	int GetGLRenderer(SDL_Window*) {
		const char* DRIVER = "opengl";
		int gl_index = -1;
		int drivers = SDL_GetNumRenderDrivers();
		for (int i = 0; i < drivers; ++i) {
			SDL_RendererInfo info;
			if (!SDL_GetRenderDriverInfo(i, &info)) {
				if (!strcmp(info.name, DRIVER)) {
					gl_index = i;
				}
			}
		}
		return gl_index;
	}

private:
	SDL_Window* window;
	SDL_GLContext context;
	SDL_Renderer* renderer;
	bool valid;
};
