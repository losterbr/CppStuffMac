# Daily C++ Quality Check

Please run the full daily quality check for this C++ project and return a concise report.

## Scope
- Use current project structure and CMake presets.
- Validate configure, build, tests, and static quality checks.
- Prefer fast checks first, then deeper checks.

## Steps
1. Configure default preset.
2. Build default preset.
3. Run all tests with output on failure.
4. Run release configure and release build.
5. Run static checks:
   - clang-tidy on project sources and tests
   - formatting check against clang-format (check only, do not rewrite unless I ask)
6. Coverage:
   - If coverage is already configured, run it and report total plus per-file weak spots.
   - If not configured, propose minimal setup and skip actual coverage run.
7. Hygiene:
   - Check git status for unexpected generated files.
   - Report stale build artifacts or temp files that should be ignored.
8. Final report:
   - pass/fail summary
   - issues sorted by severity
   - exact files affected
   - suggested fixes
   - short today action list

## Rules
- Do not commit anything.
- Do not make destructive changes.
- If a step fails, continue with independent steps and report partial results.
