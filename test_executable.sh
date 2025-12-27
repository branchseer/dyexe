#!/bin/bash

# Test script for dyexe executable
# Runs the executable and verifies the timestamp output

set -e

DYEXE="${1:-build/dyexe}"

echo "Testing $DYEXE as executable..."
echo

# Run the executable and capture its output
OUTPUT=$("$DYEXE")

echo "Executable output: $OUTPUT"

# Verify output is a valid number
if ! [[ "$OUTPUT" =~ ^[0-9]+$ ]]; then
    echo "✗ ERROR: Output is not a valid number!"
    exit 1
fi

TIMESTAMP=$OUTPUT

# Get current time
CURRENT_TIME=$(date +%s)

# Calculate difference
DIFF=$((CURRENT_TIME > TIMESTAMP ? CURRENT_TIME - TIMESTAMP : TIMESTAMP - CURRENT_TIME))

echo "Current time:  $CURRENT_TIME"
echo "Difference:    $DIFF seconds"

# Allow up to 5 seconds difference
if [ "$DIFF" -le 5 ]; then
    echo "✓ Timestamp is within acceptable range"
    echo
    echo "All tests passed!"
    exit 0
else
    echo "✗ ERROR: Timestamp differs by more than 5 seconds!"
    exit 1
fi
