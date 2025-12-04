#!/bin/bash

# NOTE: I gave up: with tiny buffer defined on the binary the test is
# desperately slow. Never saw the end. Still stuck on the first "time" call.

# --- Configuration ---
CC="gcc"
CFLAGS="-ansi -I../include -Wall -DLINUX -D_GNU_SOURCE"
LDLIBS="-L../lib -lapue"
INPUT_FILE="input_data.bin"
OUTPUT_FILE="/dev/null" # Write output to /dev/null to avoid I/O slowdown on output file
# FILE_SIZE_BYTES=536870912 # 512 MiB (2^29 bytes)
FILE_SIZE_BYTES=$((2 ** 1))

# Use the absolute path for 'time' to ensure we use the shell utility, not a built-in function
# TIME_CMD="/usr/bin/time -f \"%U %S %e\""

# --- Setup ---
echo "1. Generating large input file (${FILE_SIZE_BYTES} Bytes) to avoid caching..."
# Note: Use a device like /dev/urandom or /dev/zero for non-cached data
# We use 'dd' to create a large file of random data.
dd if=/dev/urandom of="$INPUT_FILE" bs=1M count=512 status=none
if [ $? -ne 0 ]; then
	echo "Error: Failed to create input file $INPUT_FILE. Exiting."
	exit 1
fi
echo "Input file generated: $INPUT_FILE"
echo ""

# Initialize the results table header
RESULTS_TABLE="| Buffer Size (Bytes) | User CPU (s) | System CPU (s) | Clock Time (s) | Number of Loops |
| :-----------------: | :------------: | :------------: | :-------------: | :-------------: |"

# --- Test Loop ---
echo "2. Compiling and running tests..."
for ((i = 0; i <= 19; i++)); do
	BUFFSIZE=$((1 << i))
	SUFFIX=$(printf '%06d' $BUFFSIZE)
	SOURCE_FILE="test_${SUFFIX}.c"
	EXECUTABLE="test_${SUFFIX}"

	# Calculate the theoretical number of loops
	# Total bytes / Buffer size = 2^29 / 2^i = 2^(29-i)
	NUM_LOOPS=$((1 << (29 - i)))

	# Skip files that were not successfully generated
	if [ ! -f "$SOURCE_FILE" ]; then
		echo "Warning: Source file $SOURCE_FILE not found. Skipping."
		continue
	fi

	# Compile the source file
	if ! $CC $CFLAGS "$SOURCE_FILE" -o "$EXECUTABLE" $LDLIBS; then
		echo "Error compiling $SOURCE_FILE. Skipping."
		continue
	fi

	# Run the compiled program and capture the time output
	# The time utility output (U S E) is captured into the 'metrics' variable
	metrics=$(command time -f "%U %S %e" cat "$INPUT_FILE" | ./"$EXECUTABLE" >"$OUTPUT_FILE" 2>&1)

	# metrics now contains a string like "0.01 0.15 0.16" (U S E)
	# Extract the individual components
	user_time=$(echo "$metrics" | awk '{print $1}')
	sys_time=$(echo "$metrics" | awk '{print $2}')
	clock_time=$(echo "$metrics" | awk '{print $3}')

	# Add results to the table
	RESULTS_TABLE="$RESULTS_TABLE
| $BUFFSIZE | $user_time | $sys_time | $clock_time | $NUM_LOOPS |"

	echo "Tested Buffer $BUFFSIZE. Time: $clock_time s"

	# Clean up the compiled executable to prevent clutter
	rm -f "$EXECUTABLE"

done

# --- Cleanup and Report ---
echo ""
echo "3. Cleaning up input file..."
rm -f "$INPUT_FILE"

echo ""
echo "4. Results Table"
echo ""
echo -e "$RESULTS_TABLE"
