#pragma once

#include <vector>
#include "glm/glm.hpp"

class ParticleData {
public:
	std::vector<glm::vec4> position;
	std::vector<glm::vec4> velocity;
	std::vector<glm::vec4> acceleration;
	std::vector<glm::vec4> color;
	
	ParticleData(size_t size);
	void Generate(size_t size);
	void Kill(size_t id);
	void Create(size_t id);

private:
	void Swap(size_t left, size_t right);
	
private:
	ParticleData(const ParticleData &) = delete;
    ParticleData &operator=(const ParticleData &) = delete;
};
