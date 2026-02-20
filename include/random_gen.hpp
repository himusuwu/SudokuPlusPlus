#ifndef RANDOM_GEN
#define RANDOM_GEN

#include <iostream>
#include <random>

class RandomGen
{
public:
    RandomGen();
    explicit RandomGen(unsigned int seed);
    [[nodiscard]] double random_float(double min, double max);[[nodiscard]] int random_int(int min, int max);

private:
    std::mt19937 gen;

    int max_val;
    int min_val;
};

#endif