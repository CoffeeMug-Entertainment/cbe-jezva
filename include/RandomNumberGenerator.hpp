#ifndef COFFEEBEAN_RNG
#define COFFEEBEAN_RNG

#define DEFAULT_RNG_SEED 1234567890ULL

#include <stdint.h>
#include "XoshiroCpp.hpp"

/*
struct xoshiro256ss_state {
	uint64_t s[4];
};
*/

class RandomNumberGenerator
{
public:
	RandomNumberGenerator();
	~RandomNumberGenerator();

	int rand_int(int min, int max);
	int rand_int(int max);
	double rand_double();
	bool rand_bool();
private:

	XoshiroCpp::Xoshiro256StarStar rng;

	//splitmix64

	uint64_t splitmix64Seed;

	uint64_t splitmix64();

	//One day you'll figure out how to use them with std::uniform_int_distribution, but not today 16/01/2021
	/*
	//Xoshiro256**

	xoshiro256ss_state seed;

	uint64_t rol64(uint64_t x, int k);
	
	uint64_t xoshiro256ss();
	*/
	

};

#endif