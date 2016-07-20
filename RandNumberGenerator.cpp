#include "RandNumberGenerator.h"
#include <random>


RandNumberGenerator::RandNumberGenerator()
{
}


RandNumberGenerator::~RandNumberGenerator()
{
}

int RandNumberGenerator::getRandNumb(const int v1, const int v2)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(v1, v2);

	int randNumb = dis(gen);
	return randNumb;
}
