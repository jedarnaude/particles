#include "ParticleData.h"

#include <algorithm>
#include <cassert>

namespace {

template<typename T>
void ResizeVector(T& obj, size_t size) {
	obj.clear();
	obj.resize(size);
	obj.shrink_to_fit();
}

}

ParticleData::ParticleData(size_t size) {
	Generate(size);
}

void ParticleData::Generate(size_t size) {
	this->size = size;
	count = 0;
	
	ResizeVector(position, size);
	ResizeVector(velocity, size);
	ResizeVector(acceleration, size);
	ResizeVector(color, size);
	ResizeVector(alive, size);
}

size_t ParticleData::Wake(size_t count) {
	size_t start = 0;
	size_t end = std::min(std::max(this->count + count, start), size);
	
	for (size_t i = start; i < end; ++i) {
		alive[i] = true;
	}
	this->count = end;
	
	return end;
}

void ParticleData::Kill(size_t id) {
	assert(id < size && id >= 0);
	
	if (alive[id]) {
		count--;
		alive[id] = false;
		Swap(id, count);
	}
}

void ParticleData::Swap(size_t left, size_t right) {
	std::swap(position[left],		position[right]);
	std::swap(velocity[left],		velocity[right]);
	std::swap(acceleration[left],	acceleration[right]);
	std::swap(color[left],			color[right]);
	std::swap(alive[left],			alive[right]);
}
