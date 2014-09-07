#include <OpenGL/gl3.h>

#include "Timer.h"
#include "Context.h"
#include "ParticleSystem.h"
#include "ParticleRenderer.h"
#include "ParticleUpdaters.h"
#include "ParticleGenerators.h"

struct Emitter {
	std::shared_ptr<ParticleSystem> ps;
	ParticleRenderable*				render;
};

Emitter CreateEmitter(std::unique_ptr<ParticleRenderer>& renderer) {
	Emitter emitter;
	emitter.ps = std::make_shared<ParticleSystem>(1024);
	
	std::unique_ptr<ParticleEmitter> emit(new ParticleEmitter());
	emit->Add(std::unique_ptr<SphereGenerator>(new SphereGenerator()));
	emit->SetRate(5);
	emitter.ps->Add(std::move(emit));
	emitter.ps->Add(std::unique_ptr<EulerUpdater>(new EulerUpdater()));
	
	emitter.render = renderer->Generate(*emitter.ps);
	
	return emitter;
}

int main(int argc, const char * argv[]) {
	Context ctx(1024, 768);
	
	auto renderer = ParticleRenderer::Create(ParticleRenderer::Type::GL3);
	
	// This is just a smaple, now we have components we can toy with
	View camera;
	camera.projection	= glm::perspective(90.f, 1024.f/768.f, 0.1f, 1000.f);
	camera.view			= glm::lookAt(glm::vec3(0.f, 0.f, 100.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
	camera.viewport		= glm::vec4(0.0, 0.0, 1024.0, 768.0);

	auto emitter = CreateEmitter(renderer);
	
	Timer frame;
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
					break;
				case SDL_QUIT:
					exit = true;
					break;
				default:
					break;
			}
		}

		emitter.ps->Update(frame.Get());
		renderer->Update(emitter.render, camera);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		renderer->Render(emitter.render, camera);
		
		ctx.Present();
	}
	
	renderer->Destroy(emitter.render);

    return 0;
}

