#pragma once

#include <memory>

class ParticleSystem;

struct ParticleRenderable {
};

class ParticleRenderer {
public:
	enum class Type {
		GL3,
	};

	virtual ~ParticleRenderer() = default;
	
	virtual ParticleRenderable* Generate(const ParticleSystem& ps) = 0;
	virtual void Destroy(ParticleRenderable* renderable) = 0;
	virtual void Update(ParticleRenderable* renderable) = 0;
	virtual void Render(ParticleRenderable* renderable) = 0;

	static std::unique_ptr<ParticleRenderer> Create(Type renderer);
};
