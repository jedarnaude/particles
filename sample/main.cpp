#include "Context.h"

int main(int argc, const char * argv[]) {
	Context ctx(1024, 768);
	
	bool exit = false;
	while (!exit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						exit = true;
						break;
					}
				case SDL_QUIT:
					exit = true;
					break;
				default:
					break;
			}
		}
		
		ctx.Present();
	}

    return 0;
}

