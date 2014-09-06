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

void ParticleEmitter::SetRate(float rate) {
	rate_ = rate;
}

float ParticleEmitter::GetRate() {
	return rate_;
}
