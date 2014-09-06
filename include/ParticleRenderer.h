#pragma once

#include <memory>

class ParticleSystem;

class ParticleRenderer {
public:
	enum class Type {
		GL32,
	};

	virtual ~ParticleRenderer() = default;
	
	virtual void Generate(const ParticleSystem& ps) = 0;
	virtual void Destroy(const ParticleSystem& ps) = 0;
	virtual void Update(const ParticleSystem& ps) = 0;
	virtual void Render(const ParticleSystem& ps) = 0;

	static std::unique_ptr<ParticleRenderer> Create(Type& renderer);
};
