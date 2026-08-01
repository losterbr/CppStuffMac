# CppStuffMac

Small C++ experiments around complex numbers, Mandelbrot set membership, terminal color output, and a plotting demo.

The project is organized as testable libraries plus thin executable entrypoints, with CMake presets for reproducible local builds.

## Targets

- `Main`: interactive Mandelbrot membership prompt for a user-provided complex value.
- `Plotting`: generates sampled function data or Mandelbrot-set image data and plots it through `gnuplot`.
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
- Build: `Build Interactive Mandelbrot`, `Build Plotting App`, `Build Complex Number Unit Tests`, `Build App Logic Unit Tests`
- Run (No Debugger, from Run/Debug menu): `Run Interactive Mandelbrot (No Debugger)`
- Debug (LLDB): `Debug Interactive Mandelbrot`, `Run Plotting App (Interactive GNUplot Window)`, `Run Mandelbrot Plot (Interactive GNUplot Window)`, `Run Plotting App (No GNUplot, Non-interactive)`, `Run Complex Number Unit Tests`, `Run App Logic Unit Tests`

The interactive plotting launch passes `--gnuplot`; without that flag the `Plotting` executable stays non-interactive. Use `--mandelbrot` to render a Mandelbrot image.

For Mandelbrot zooming, the plotting executable accepts viewport flags:

- `--xmin`, `--xmax`, `--ymin`, `--ymax`
- `--width`, `--height`, `--max-iterations`

Example:

```bash
.build/default/bin/Plotting --mandelbrot --gnuplot --width 1200 --height 900 --max-iterations 1200 --xmin -0.8 --xmax -0.7 --ymin 0.05 --ymax 0.15
```

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
