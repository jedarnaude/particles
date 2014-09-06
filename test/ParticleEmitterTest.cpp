#include "gmock/gmock.h"
#include "ParticleSystem.h"

using ::testing::_;

class MockGenerator : public ParticleGenerator {
public:
	MOCK_METHOD4(Generate,
		void(double dt, ParticleData& particles, size_t start, size_t end));
};

TEST(ParticleEmitterTest, DefaultEmitter) {
	ParticleEmitter emitter;
	ParticleData data;
	std::unique_ptr<MockGenerator> mock(new MockGenerator());
	
	EXPECT_CALL(*mock.get(), Generate(_, _, _, _)).Times(2);
	
	emitter.Add(std::move(mock));
	emitter.Emit(0.0, data);
	emitter.Emit(0.0, data);
}
