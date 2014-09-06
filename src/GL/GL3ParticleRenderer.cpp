#include "GL3ParticleRenderer.h"
#include "ParticleSystem.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GL3ParticleRenderable::GL3ParticleRenderable(const ParticleSystem& ps)
	: vao(0)
	, vbo(0)
	, program(0)
	, vertices(new Vertex[ps.GetParticles().size])
	, ps(ps) {
}

GL3ParticleRenderer::GL3ParticleRenderer() {
	// Shaders
}

GL3ParticleRenderer::~GL3ParticleRenderer() {
}

ParticleRenderable* GL3ParticleRenderer::Generate(const ParticleSystem& ps) {
	// Renderable
	renderables_.emplace_back(GL3ParticleRenderable(ps));
	GL3ParticleRenderable* render = &renderables_.back();

	// VBO
	auto& particles = ps.GetParticles();
 
	glGenVertexArrays(1, &render->vao);
	glBindVertexArray(render->vao);
 
	// In the future I will subdivide this into dynamic and static data within a particle system, this is slower than usual at this moment
	glGenBuffers(1, &render->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, render->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL3ParticleRenderable::Vertex) * particles.size, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);

	// Vertex attribs
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GL3ParticleRenderable::Vertex), BUFFER_OFFSET(0));
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GL3ParticleRenderable::Vertex), BUFFER_OFFSET(sizeof(glm::vec4)));
 
	return render;
}

void GL3ParticleRenderer::Destroy(ParticleRenderable* renderable) {
	GL3ParticleRenderable* render = static_cast<GL3ParticleRenderable*>(renderable);

	if (render->vbo) {
		glDeleteBuffers(1, &render->vbo);
	}
}

void GL3ParticleRenderer::Update(ParticleRenderable* renderable) {
	GL3ParticleRenderable* render = static_cast<GL3ParticleRenderable*>(renderable);
	auto& particles = render->ps.GetParticles();

	// Avoid stalls as data is completely uploaded
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL3ParticleRenderable::Vertex) * particles.size, nullptr, GL_STREAM_DRAW);
	
	// Map data (slow due to AoS/SoA conversion)
	auto buffer = (GL3ParticleRenderable::Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (buffer != nullptr) {
		for (int i = 0; i < particles.count; ++i) {
			buffer[i].position = particles.position[i];
			buffer[i].color = particles.color[i];
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

void GL3ParticleRenderer::Render(ParticleRenderable* renderable) {
	GL3ParticleRenderable* render = static_cast<GL3ParticleRenderable*>(renderable);

	auto count = render->ps.GetParticles().count;
	
	if (count > 0) {
		glBindVertexArray(render->vao);
		glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(count));
	}
}
