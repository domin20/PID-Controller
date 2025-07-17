#pragma once

#include <stdint.h>

using ClockSource = uint64_t (*)();

inline constexpr float INVERSE_EULER = 0.368f; // inverse euler
