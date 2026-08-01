# Pre-Commit Gate For C++

Run a strict pre-commit gate on the current changes and tell me if this is safe to commit.

## Scope
- Focus on staged and unstaged changed files first, then full-project sanity where needed.

## Steps
1. Show git status and summarize changed files by type:
   - source
   - headers
   - tests
   - CMake/tooling
2. Build and test:
   - configure default preset
   - build default preset
   - run full tests
3. Quality checks on changed files:
   - clang-tidy (detect via `command -v clang-tidy`; do not use `xcrun -f clang-tidy`)
   - formatting compliance check
4. Risk checks:
   - accidental debug code
   - dead code or commented-out blocks
   - noisy logging
   - missing tests for behavior changes
   - suspicious API or ABI changes
5. Coverage delta:
   - If coverage is configured, report whether changed lines are covered.
   - Enforce minimum overall project coverage (src + apps) > 90%; treat this as blocking.
   - If not configured, identify impacted code paths lacking tests.
6. Commit recommendation:
   - commit ready: yes/no
   - blocking issues
   - non-blocking improvements
   - suggested commit message

## Rules
- Do not auto-fix or auto-commit unless I explicitly ask.
- Keep output decision-oriented and concise.
- Tool detection fallback:
   - If clang-tidy is missing, report it as an environment/tooling blocker with install guidance.
   - Continue running all other independent pre-commit checks and still produce a final gate decision.
