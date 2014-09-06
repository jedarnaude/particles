#pragma once

#include <list>
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"

#include "ParticleRenderer.h"

struct GL3ParticleRenderable : public ParticleRenderable {
	struct Vertex {
		glm::vec4 position;
		glm::vec4 color;
	};

	GLuint vao;
	GLuint vbo;
	GLuint program;
	std::unique_ptr<Vertex[]> vertices;
	
	const ParticleSystem& ps;
	
	GL3ParticleRenderable(const ParticleSystem& ps);
};

class GL3ParticleRenderer : public ParticleRenderer {
public:
	GL3ParticleRenderer();
	virtual ~GL3ParticleRenderer();
	
	virtual ParticleRenderable* Generate(const ParticleSystem& ps) override;
	virtual void Destroy(ParticleRenderable* renderable) override;
	virtual void Update(ParticleRenderable* renderable) override;
	virtual void Render(ParticleRenderable* renderable) override;
	
private:
	std::list<GL3ParticleRenderable> renderables_;
};