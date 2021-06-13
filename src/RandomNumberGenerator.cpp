#include "RandomNumberGenerator.hpp"
#include <chrono>
#include <random>

RandomNumberGenerator::RandomNumberGenerator()
{
	
	splitmix64Seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	/*
	for (int i = 0; i < 4; ++i)
	{
		this->seed.s[i] = splitmix64();
	}
	*/

	rng = XoshiroCpp::Xoshiro256StarStar(splitmix64());
}

RandomNumberGenerator::~RandomNumberGenerator()
{

}

int RandomNumberGenerator::rand_int(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);

	return dist(rng);
}

int RandomNumberGenerator::rand_int(int max)
{
	std::uniform_int_distribution<int> dist(0, max);

	return dist(rng);
}

double RandomNumberGenerator::rand_double()
{
	return XoshiroCpp::DoubleFromBits(rng());
}

bool RandomNumberGenerator::rand_bool()
{
	return rand_double() > 0.5;
}


uint64_t RandomNumberGenerator::splitmix64() {

	//uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	uint64_t z = (splitmix64Seed += UINT64_C(0x9E3779B97F4A7C15));
	z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
	return z ^ (z >> 31);
}
/*
uint64_t RandomNumberGenerator::rol64(uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

uint64_t RandomNumberGenerator::xoshiro256ss()
{
	uint64_t *s = this->seed.s;
	uint64_t const result = rol64(s[1] * 5, 7) * 9;
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return result;
}
*/