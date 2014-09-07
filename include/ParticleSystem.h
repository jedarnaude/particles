#pragma once

#include "ParticleData.h"

struct Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class ParticleGenerator {
public:
	virtual ~ParticleGenerator() = default;
	virtual void Generate(double dt, ParticleData& particles, size_t start, size_t end) = 0;
};

class ParticleUpdater {
public:
	virtual ~ParticleUpdater() = default;
	virtual void Update(double dt, ParticleData& particles) = 0;
};

class ParticleEmitter {
public:
	void Emit(double dt, ParticleData& particles);
	void Add(std::unique_ptr<ParticleGenerator>&& generator);
	void SetRate(int rate);

private:
	std::vector<std::unique_ptr<ParticleGenerator>> generators_;
	double ratio_;
	double emit_;
	int rate_;
};

class ParticleSystem {
public:
	Transform transform;

public:
	explicit ParticleSystem(size_t max_particles);
		
	void Update(double dt);
	
	void Add(std::unique_ptr<ParticleEmitter>&& emitter);
	void Add(std::unique_ptr<ParticleUpdater>&& updater);
	
	const ParticleData& GetParticles() const {
		return particles_;
	}
	
	static size_t GetMemory(const ParticleSystem& system);
	
private:
	ParticleData particles_;
	std::vector<std::unique_ptr<ParticleEmitter>> emitters_;
	std::vector<std::unique_ptr<ParticleUpdater>> updaters_;

private:
	ParticleSystem(const ParticleSystem &) = delete;
	ParticleSystem &operator=(const ParticleSystem &) = delete;
};
