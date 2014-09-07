#include "ParticleGenerators.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

void SphereGenerator::Generate(double dt, ParticleData& particles, size_t start, size_t end) {
	for (size_t i = start; i < end; ++i) {
		auto position = glm::sphericalRand(1.0);
		auto direction = glm::normalize(position + position) * (double)glm::linearRand(min_speed, max_speed);
		particles.position[i] = glm::vec4(position, 1.0);
		particles.velocity[i] = glm::vec4(direction, 0.0);
		particles.color[i] = glm::vec4(glm::sphericalRand(1.0), 1.0);
	}
}
