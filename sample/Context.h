#pragma once

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>

#include <iostream>

class Context {
public:
	Context(unsigned width, unsigned height)
	: window(nullptr)
	, valid(false) {

		SDL_Init(SDL_INIT_VIDEO);
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetSwapInterval(1);
	
		window = SDL_CreateWindow("sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		context = SDL_GL_CreateContext(window);

		std::cout << glGetString(GL_VERSION) << std::endl;

		if (!window || !context) {
			return;
		}
		
		valid = true;
	}
	
	~Context() {
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();
		window = nullptr;
	}

	void Present() {
		SDL_GL_SwapWindow(window);
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
	bool valid;
};
