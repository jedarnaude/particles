#pragma once

#include "ParticleSystem.h"

class SphereGenerator : public ParticleGenerator {
public:
	float min_speed{ 1.0f };
	float max_speed{ 5.0f };
	float radius{ 5.0f };
 
	virtual void Generate(double dt, ParticleData& particles, size_t start, size_t end) override;
};
