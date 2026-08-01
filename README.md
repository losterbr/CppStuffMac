# CppStuffMac

Small C++ experiments around complex numbers, Mandelbrot set membership, terminal color output, and a plotting demo.

The project is organized as testable libraries plus thin executable entrypoints, with CMake presets for reproducible local builds.

## Targets

- `Main`: prints sample complex output and a Mandelbrot membership check.
- `Plotting`: generates sample data and plots it through `gnuplot`.
- `TestComplexNumbers`: unit tests for the complex number type.
- `TestMandelbrot`: unit tests for Mandelbrot membership behavior.
- `TestApps`: unit tests for app-layer logic (`main_app`, `plotting_app`).

## Requirements

- CMake 3.21+
- A C++20+ compiler (the build enables C++23 automatically when the toolchain supports it)
- Optional: `gnuplot` for the plotting demo

## Build

```bash
cmake --preset default
cmake --build --preset default --parallel
```

This preset configures `Unix Makefiles` into `.build/default` and also generates a compilation database at:

- `.build/default/compile_commands.json`

## Test

```bash
ctest --preset default --parallel
```

You can also run individual test executables from `.build/default/bin/`.

## Coverage Build

```bash
cmake --preset coverage
cmake --build --preset coverage --parallel
ctest --preset coverage --parallel
./scripts/coverage_report.sh .build/coverage .build/coverage-report
```

The coverage preset enables compiler instrumentation flags (`--coverage`) for supported toolchains.
The coverage script keeps generated `.gcov` files inside `.build/coverage-report/gcov-files`.

## VS Code

The workspace includes ready-to-use tasks and debug configurations:

- Configure: `CMake Configure (default)`
- Build: `Build Main App`, `Build Plotting App`, `Build Complex Number Unit Tests`, `Build Mandelbrot Membership Tests`, `Build App Logic Unit Tests`
- Run (No Debugger, from Run/Debug menu): `Run Main App (No Debugger, Interactive Mandelbrot Prompt)`
- Debug (LLDB): `Debug Main App (Interactive Mandelbrot Prompt)`, `Run Plotting App (Interactive GNUplot Window)`, `Run Plotting App (No GNUplot, Non-interactive)`, `Run Complex Number Unit Tests`, `Run Mandelbrot Membership Unit Tests (Non-interactive)`, `Run App Logic Unit Tests`
- Task-based no-debug fallback: `Run Main App (No Debugger, Interactive Mandelbrot Prompt)`

The interactive plotting launch passes `--gnuplot`; without that flag the `Plotting` executable stays non-interactive.

For interactive input on macOS, prefer the no-debug run option first. It avoids debugger architecture friction and provides reliable stdin prompts.

## Project Layout

- `include/`: public headers
- `src/`: core library implementation files
- `apps/`: executable entrypoints and app-layer logic
- `tests/unit/`: unit tests
- `scripts/`: local automation scripts (coverage reporting)
- `cmake/`: CMake helper modules
- `CMakeLists.txt`: top-level project definition
- `CMakePresets.json`: reproducible local build and test presets
