#pragma once
#include <random>
static std::mt19937_64 randenginefixed(1337);
static std::mt19937_64 randengine(std::random_device{}());