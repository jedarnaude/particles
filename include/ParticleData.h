#pragma once

#include <vector>
#include "glm/glm.hpp"

class ParticleData {
public:
	std::vector<glm::vec4>	position;
	std::vector<glm::vec4>	velocity;
	std::vector<glm::vec4>	acceleration;
	std::vector<glm::vec4>	color;
	std::vector<bool>		alive;
	size_t size;
	size_t count;
	
public:
	ParticleData();

	void Generate(size_t size);
	size_t Wake(size_t count);
	void Kill(size_t id);

private:
	void Swap(size_t left, size_t right);
	
private:
	ParticleData(const ParticleData &) = delete;
    ParticleData &operator=(const ParticleData &) = delete;
};
