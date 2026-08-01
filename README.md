# CppStuffMac

Small C++ experiments around complex numbers, Mandelbrot set membership, terminal color output, and a plotting demo.

## Targets

- `Main`: prints sample complex output and a Mandelbrot membership check.
- `Plotting`: generates sample data and plots it through `gnuplot`.
- `TestComplexNumbers`: unit tests for the complex number type.
- `TestMandelbrot`: unit tests for Mandelbrot membership behavior.

## Requirements

- CMake 3.21+
- A C++20 compiler
- Ninja (recommended through `CMakePresets.json`)
- Optional: `gnuplot` for the plotting demo

## Build

```bash
cmake --preset default
cmake --build --preset default
```

This preset also generates a compilation database at:

- `.build/default/compile_commands.json`

## Test

```bash
ctest --preset default
```

## Coverage Build

```bash
cmake --preset coverage
cmake --build --preset coverage
ctest --preset coverage
```

The coverage preset enables compiler instrumentation flags (`--coverage`) for supported toolchains.

## Project Layout

- `include/`: public headers
- `src/`: library implementation files
- `apps/`: runnable executables (`Main`, `Plotting`)
- `tests/unit/`: unit tests
- `cmake/`: CMake helper modules
- `CMakeLists.txt`: top-level project definition
- `CMakePresets.json`: reproducible local build and test presets
