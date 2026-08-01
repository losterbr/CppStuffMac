#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${1:-.build/coverage}"
REPORT_DIR="${2:-.build/coverage-report}"
GCOV_DIR="${REPORT_DIR}/gcov-files"
SUMMARY_FILE="${REPORT_DIR}/gcov-summary.txt"
TSV_FILE="${REPORT_DIR}/project-coverage.tsv"

if [[ ! -d "${BUILD_DIR}" ]]; then
  echo "error: build directory not found: ${BUILD_DIR}" >&2
  exit 1
fi

rm -rf "${GCOV_DIR}"
mkdir -p "${GCOV_DIR}"
: > "${SUMMARY_FILE}"

gcno_files=()
while IFS= read -r file; do
  gcno_files+=("${file}")
done < <(find "${BUILD_DIR}" -path '*/CMakeFiles/*.dir/*.cpp.gcno' | sort)

if [[ ${#gcno_files[@]} -eq 0 ]]; then
  echo "error: no .gcno files found under ${BUILD_DIR}" >&2
  exit 1
fi

for gcno in "${gcno_files[@]}"; do
  (
    cd "${GCOV_DIR}"
    gcov -b -c "${gcno}"
  ) >> "${SUMMARY_FILE}" 2>&1
  echo >> "${SUMMARY_FILE}"
done

awk '
  /^File '\''/ {
    file=$2
    gsub("'\''", "", file)
  }
  /^Lines executed:/ {
    line=$0
    sub(/^Lines executed:/, "", line)
    split(line, parts, "% of ")
    pct=parts[1]+0
    lines=parts[2]+0
    if (file ~ /(^|\/)src\/|(^|\/)apps\//) {
      total_lines += lines
      covered_lines += (pct / 100.0) * lines
      printf "%s\t%.2f%%\t%d lines\n", file, pct, lines
    }
  }
  END {
    if (total_lines > 0) {
      overall=(covered_lines / total_lines) * 100.0
      printf "OVERALL_PROJECT\t%.2f%%\t%d lines\n", overall, total_lines
    }
  }
' "${SUMMARY_FILE}" | tee "${TSV_FILE}"

echo "gcov output directory: ${GCOV_DIR}"
echo "coverage summary: ${TSV_FILE}"
