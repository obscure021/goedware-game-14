#!/bin/bash

set -e  # Stop on first error

# Timestamp for binary naming
timestamp=$(date +"%Y-%m-%d_%H-%M-%S")

# Build directory
mkdir -p build
cd build

# Configure and build
cmake .. > /dev/null
make > /dev/null

# Verify binary exists
if [[ ! -f ./bin/main ]]; then
    echo "Error: ./bin/main not found."
    exit 1
fi

# Copy binary with timestamp
mkdir -p ../builds
cp ./bin/main "../builds/main_$timestamp"

# Run the binary
"../builds/main_$timestamp"
