#include "ParticleUpdaters.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <iostream>

void EulerUpdater::Update(double dt, ParticleData& particles) {
	for (size_t i = 0; i < particles.count; ++i) {
		particles.acceleration[i] += 0.f;
		particles.velocity[i] += float(dt) * particles.acceleration[i];
		particles.position[i] += float(dt) * particles.velocity[i];
	}
}
