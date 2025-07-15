#pragma once

#include <stdint.h>

using TimeSource = uint64_t (*)();

inline constexpr uint8_t MAX_ORDER = 4;
