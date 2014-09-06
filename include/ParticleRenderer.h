#pragma once

#include <memory>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class ParticleSystem;

struct ParticleRenderable {
};

struct View {
	glm::mat4 projection;
	glm::mat4 view;
	glm::vec4 viewport;
};

class ParticleRenderer {
public:
	enum class Type {
		GL3,
	};

	virtual ~ParticleRenderer() = default;
	
	virtual ParticleRenderable* Generate(const ParticleSystem& ps) = 0;
	virtual void Destroy(ParticleRenderable* renderable) = 0;
	virtual void Update(ParticleRenderable* renderable, View& view) = 0;
	virtual void Render(ParticleRenderable* renderable, View& view) = 0;

	static std::unique_ptr<ParticleRenderer> Create(Type renderer);
};
