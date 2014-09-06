#include "gmock/gmock.h"
#include "ParticleData.h"

struct ParticleDataTest : public ::testing::Test {
	ParticleDataTest() {
		data.Generate(10);
	}
	
	ParticleData data;
};

TEST_F(ParticleDataTest, Generate) {
	// Implicit generation
    EXPECT_EQ(data.size, data.position.size());
    EXPECT_EQ(data.size, data.color.size());
    EXPECT_EQ(10, data.size);
    EXPECT_EQ(0, data.count);
	
	// Explicit generation
	data.Generate(20);
    EXPECT_EQ(data.size, data.acceleration.size());
    EXPECT_EQ(data.size, data.velocity.size());
    EXPECT_EQ(20, data.size);
    EXPECT_EQ(0, data.count);
}

TEST_F(ParticleDataTest, Wake) {
	// Wake once
	size_t count = 4;
	data.Wake(count);
	for (size_t i = 0; i < count; ++i) {
		EXPECT_TRUE(data.alive[i]);
	}
	for (size_t i = data.count; i < data.size; ++i) {
		EXPECT_FALSE(data.alive[i]);
	}
    EXPECT_EQ(count, data.count);
    EXPECT_EQ(10, data.size);
	
	// Wake again
	count += 2;
	data.Wake(2);
	for (size_t i = 0; i < count; ++i) {
		EXPECT_TRUE(data.alive[i]);
	}
	for (size_t i = data.count; i < data.size; ++i) {
		EXPECT_FALSE(data.alive[i]);
	}
    EXPECT_EQ(count, data.count);
    EXPECT_EQ(10, data.size);
}

TEST_F(ParticleDataTest, WakeOverLimit) {
	EXPECT_EQ(data.size, data.Wake(20));
    EXPECT_EQ(data.size, data.count);
    EXPECT_EQ(10, data.size);
	for (auto alive : data.alive) {
		EXPECT_TRUE(alive);
	}
}

TEST_F(ParticleDataTest, Kill) {
	data.Wake(5);
	EXPECT_EQ(5, data.count);
	
	// Kill one guy
	EXPECT_TRUE(data.alive[3]);
	data.Kill(3);
	EXPECT_TRUE(data.alive[3]);	// It was replaced
	EXPECT_EQ(4, data.count);
	
	// Kill replacement
	data.Kill(3);
	EXPECT_FALSE(data.alive[3]);
	EXPECT_EQ(3, data.count);
	
	// Kill all
	while (data.count) {
		size_t id = data.count - 1;
		EXPECT_TRUE(data.alive[id]);
		data.Kill(data.count - 1);
		EXPECT_FALSE(data.alive[id]);
	}
}

TEST_F(ParticleDataTest, KillDead) {
	data.Wake(2);
	EXPECT_TRUE(data.alive[1]);
	data.Kill(1);
	EXPECT_FALSE(data.alive[1]);
	data.Kill(1);
	EXPECT_FALSE(data.alive[1]);
	EXPECT_EQ(1, data.count);
}

TEST_F(ParticleDataTest, KillEmpty) {
	EXPECT_FALSE(data.alive[1]);
	EXPECT_EQ(0, data.count);
	data.Kill(1);
	EXPECT_FALSE(data.alive[1]);
	EXPECT_EQ(0, data.count);
}
