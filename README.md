# PID Controller (C++)

A lightweight, clean C++ library implementing a PID (Proportional-Integral-Derivative) controller. Designed for embedded or performance-critical systems — no dynamic memory allocation, minimal dependencies, and customizable time base.

## Project Structure

```bash
pid-controller/
├── include/ # Headers
│ ├── Config.h
│ ├── Derivative.h
│ ├── Inertia.h
│ ├── Integral.h
│ └── PID.h
├── src/ # Impl
│ ├── Derivative.cpp
│ ├── Integral.cpp
│ └── PID.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## API Overview

- `PID` — Main controller class
- `Integral`, `Derivative`, `Inertia` — Internal components
- `TimeSource` — A function pointer: `using TimeSource = uint64_t (*)();`  
  Should return current time in **milliseconds**

## Quick Start

```bash
mkdir build && cd build
cmake ..
make
