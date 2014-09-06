#include "ParticleSystem.h"

void ParticleEmitter::Emit(double dt, ParticleData& particles) {
	const size_t start = particles.count;
	const size_t end = particles.Wake(static_cast<size_t>(dt * rate_));
 
	for (auto& generator : generators_) {
		generator->Generate(dt, particles, start, end);
	}
}

void ParticleEmitter::Add(std::unique_ptr<ParticleGenerator>&& generator) {
	generators_.push_back(std::move(generator));
}

float ParticleEmitter::Rate(float rate) {
	rate_ = rate;
	return rate;
}

float ParticleEmitter::Rate() {
	return rate_;
}
