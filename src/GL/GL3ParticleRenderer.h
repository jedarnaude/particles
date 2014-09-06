#pragma once

#include "ParticleRenderer.h"
#include <OpenGL/gl3.h>

class GL3ParticleRenderer : public ParticleRenderer {
public:
	virtual ~GL3ParticleRenderer();
	
	virtual void Generate(const ParticleSystem& ps) override;
	virtual void Destroy(const ParticleSystem& ps) override;
	virtual void Update(const ParticleSystem& ps) override;
	virtual void Render(const ParticleSystem& ps) override;
	
private:
	
};