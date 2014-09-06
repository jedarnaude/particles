#include <OpenGL/gl3.h>

#include "Context.h"
#include "ParticleSystem.h"
#include "ParticleRenderer.h"

int main(int argc, const char * argv[]) {
	Context ctx(1024, 768);
	
	auto renderer = ParticleRenderer::Create(ParticleRenderer::Type::GL3);
	
	// This is just a smaple, now we have components we can toy with
	ParticleSystem ps(1024);
	ParticleRenderable* ps_render = renderer->Generate(ps);
	
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

		renderer->Update(ps_render);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		renderer->Render(ps_render);
		
		ctx.Present();
	}
	
	renderer->Destroy(ps_render);

    return 0;
}

