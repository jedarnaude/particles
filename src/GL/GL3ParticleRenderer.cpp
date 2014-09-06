#include "GL3ParticleRenderer.h"
#include "GLSL3ParticleShaders.cpp"
#include "GLUtils.h"
#include "ParticleSystem.h"
#include "glm/ext.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GL3ParticleRenderable::GL3ParticleRenderable(const ParticleSystem& ps)
	: vao(0)
	, vbo(0)
	, vertices(new Vertex[ps.GetParticles().size])
	, ps(ps) {
}

GL3ParticleRenderer::GL3ParticleRenderer() {
	// Shaders
	GLuint vertex	= CompileShader(GL_VERTEX_SHADER, vertex_point_sprite);
	GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragment_point_sprite);
	if (vertex == 0 || fragment == 0) {
		return;
	}
	
	program = LinkShader(vertex, fragment, [](GLuint program) {
		glBindAttribLocation(program, 0, "aPosition");
		glBindAttribLocation(program, 1, "aColor");
		
		glBindFragDataLocation(program, 0, "oFragColor");
	});
}

GL3ParticleRenderer::~GL3ParticleRenderer() {
	if (program) {
		glDeleteProgram(program);
	}
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

	// Vertex attribs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GL3ParticleRenderable::Vertex), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GL3ParticleRenderable::Vertex), BUFFER_OFFSET(sizeof(glm::vec4)));
 
	return render;
}

void GL3ParticleRenderer::Destroy(ParticleRenderable* renderable) {
	GL3ParticleRenderable* render = static_cast<GL3ParticleRenderable*>(renderable);

	if (render->vbo) {
		glDeleteBuffers(1, &render->vbo);
	}
}

void GL3ParticleRenderer::Update(ParticleRenderable* renderable, View& view) {
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
	
	// Update model matrix
	glm::mat4 mat;
	render->model = glm::translate(mat, render->ps.transform.position);
}

void GL3ParticleRenderer::Render(ParticleRenderable* renderable, View& view) {
	GL3ParticleRenderable* render = static_cast<GL3ParticleRenderable*>(renderable);

	auto count = render->ps.GetParticles().count;
	
	if (count > 0) {
		glPointSize(20);
		glUseProgram(program);
		
		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view.projection * view.view * render->model));
		glBindVertexArray(render->vao);
		glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(count));
	}
}
