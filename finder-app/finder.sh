#!/usr/bin/env bash
set -euo pipefail

if [ $# -ne 2 ]; then
  echo "Error: two arguments required: <filesdir> <searchstr>" >&2
  exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d "$filesdir" ]; then
  echo "Error: $filesdir is not a directory" >&2
  exit 1
fi

file_count=$(find "$filesdir" -type f | wc -l)
match_count=$(grep -r -n --exclude-dir=".git" -- "$searchstr" "$filesdir" | wc -l || true)

echo "The number of files are $file_count and the number of matching lines are $match_count"
