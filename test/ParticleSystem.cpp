#include "gmock/gmock.h"
#include "ParticleSystem.h"

TEST(ParticleSystemTest, ComputeMemory) {
	ParticleSystem ps(1024);
	
	EXPECT_EQ(66880, ParticleSystem::GetMemory(ps));
}

TEST(ParticleSystemTest, Update) {
}
