#pragma once

#include "ParticleData.h"

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
	virtual ~ParticleEmitter() = default;
	virtual void Emit(double dt, ParticleData& particles);
	
	void Add(std::unique_ptr<ParticleGenerator>&& generator);

	float Rate(float rate);
	float Rate();
	
private:
	std::vector<std::unique_ptr<ParticleGenerator>> generators_;
	float rate_;
};
