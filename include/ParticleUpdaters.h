#pragma once

#include "ParticleSystem.h"

class EulerUpdater : public ParticleUpdater {
public:
	virtual void Update(double dt, ParticleData& particles) override;
};