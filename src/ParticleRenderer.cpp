#include "ParticleRenderer.h"
#include "GL/GL3ParticleRenderer.h"

std::unique_ptr<ParticleRenderer> ParticleRenderer::Create(Type renderer) {
	switch (renderer) {
		case Type::GL3:	return std::unique_ptr<GL3ParticleRenderer>(new GL3ParticleRenderer);
	}
	
	return nullptr;
}
