#include "random_gen.hpp"

RandomGen::RandomGen()
{
    std::random_device rd;
    gen.seed(rd());
}

RandomGen::RandomGen(unsigned int seed) : gen(seed) {}

[[nodiscard]] double RandomGen::random_float(double min, double max)
{
    std::uniform_real_distribution<double> dist(min, max);

    return dist(gen);
}

[[nodiscard]] int RandomGen::random_int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}
