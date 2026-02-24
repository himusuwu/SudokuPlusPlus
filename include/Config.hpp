#ifndef CONFIG
#define CONFIG

#include <cstddef>
#include <cstdint>

enum class DifficultyLevel : uint8_t
{
    EASY,
    MEDIUM,
    HARD,
    EXPERT
};

struct DifficultyProfile
{
    size_t minEmpty;
    size_t maxEmpty;
    bool symmetric;
    size_t solverAttempts;
};

#endif
