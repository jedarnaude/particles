#include "ParticleSystem.h"

namespace {

template<typename T>
size_t STLMemory(T& obj) {
	using Type = typename T::value_type;
	return obj.capacity() * sizeof(Type);
}

}

void ParticleEmitter::Emit(double dt, ParticleData& particles) {
	const size_t start = particles.count;
	const size_t end = particles.Wake(static_cast<size_t>(dt * rate));
 
	for (auto& generator : generators_) {
		generator->Generate(dt, particles, start, end);
	}
}

void ParticleEmitter::Add(std::unique_ptr<ParticleGenerator>&& generator) {
	generators_.emplace_back(std::move(generator));
}

ParticleSystem::ParticleSystem(size_t max_particles) {
	particles_.Generate(max_particles);
}
		
void ParticleSystem::Update(double dt) {
	for (auto& emitter : emitters_) {
		emitter->Emit(dt, particles_);
	}

	for (auto& updater : updaters_) {
		updater->Update(dt, particles_);
	}
}
	
void ParticleSystem::Add(std::unique_ptr<ParticleEmitter>&& emitter) {
	emitters_.emplace_back(std::move(emitter));
}

void ParticleSystem::Add(std::unique_ptr<ParticleUpdater>&& updater) {
	updaters_.emplace_back(std::move(updater));
}

size_t ParticleSystem::GetMemory(const ParticleSystem& system) {
	size_t size = sizeof(system);
	size += ParticleData::GetMemory(system.particles_);
	size += STLMemory(system.emitters_);
	size += STLMemory(system.updaters_);
	// Not completely true as we are missing size of emitters/generators/updaters
	return size;
}
